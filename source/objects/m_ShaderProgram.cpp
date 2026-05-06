
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>

#include "bgfx/bgfx.h"

#include "enums/m_ShaderType.h"
#include "objects/m_Renderer.h"

#include "services/m_Directory.h"
#include "objects/m_ShaderProgram.h"

namespace Mariner {

    namespace Objects {

        m_ShaderProgram* m_ShaderProgram::New() {

            m_ShaderProgram* Instance = new m_ShaderProgram();
            Instance->Name = "ShaderProgram";
            Instance->ClassName = "m_ShaderProgram";
            return Instance;

        }

        void m_ShaderProgram::AddShader(Mariner::Objects::m_ShaderScript* Script) {

            this->LinkedScripts.Add(Script);

        }

        void m_ShaderProgram::RemoveShader(Mariner::Objects::m_ShaderScript* Script) {

            this->LinkedScripts.Remove(Script);

        }

        /**
         * Pheeeeeeeee, Ava McPheeeeeeeee. BGFX's shader API is particularly shitty
         * in the sense that it expects a binary representation of a proprietery 
         * shading language, and doesnt give us any API to compile it.
         * Fuck meeeeeeeeeee.
         */
        void m_ShaderProgram::Compile() {

            auto Renderer = Mariner::Objects::m_Renderer::New();
            auto DirectoryService = Mariner::Services::m_Directory::New();

            auto ShadercPath = DirectoryService->GetContentDirectory() + "/bin/shaderc";
            auto DefinesPath = DirectoryService->GetContentDirectory() + "/shaders/m_Defs.def.sc";
            auto IncludePath = DirectoryService->GetVendoredDirectory() + "/bgfx/src";

            bgfx::ShaderHandle VertexShaderHandle = BGFX_INVALID_HANDLE;
            bgfx::ShaderHandle FragmentShaderHandle = BGFX_INVALID_HANDLE;

            for (auto Script : this->LinkedScripts) {

                if (Script->SourceContent) {

                    throw std::runtime_error("m_Content source not supported on ShaderScript");

                }

                bool IsFragment = Script->ShaderType == Mariner::Enums::m_ShaderType::FRAGMENT;

                Mariner::Libraries::m_String TypeFlag = IsFragment ? "fragment" : "vertex";
                Mariner::Libraries::m_String InputPath = Mariner::Libraries::m_String("/tmp/mariner_shader_") + TypeFlag + ".sc";
                Mariner::Libraries::m_String OutputPath = Mariner::Libraries::m_String("/tmp/mariner_shader_") + TypeFlag + ".bin";

                {

                    std::ofstream TempFile(InputPath.ToCString());
                    if (!TempFile.is_open()) {

                        throw std::runtime_error("Failed to write temp shader source");

                    }

                    TempFile << Script->Source.ToCString();

                }

                std::vector<const char*> Argv = {

                    ShadercPath.ToCString(),
                    "-f", InputPath.ToCString(),
                    "-o", OutputPath.ToCString(),
                    "--type", TypeFlag.ToCString(),
                    "--platform", "osx",
                    "-i", IncludePath.ToCString(),
                    "-p", Renderer->GetShaderLanguageType().ToCString(),
                    "--varyingdef", DefinesPath.ToCString(), 
                    nullptr

                };

                pid_t PID = fork();
                if (PID < 0) {

                    throw std::runtime_error("fork() failed");

                }

                if (PID == 0) {

                    execv(ShadercPath.ToCString(), const_cast<char* const*>(Argv.data()));
                    _exit(1);

                }

                int Status = 0;
                waitpid(PID, &Status, 0);

                if (!WIFEXITED(Status) || WEXITSTATUS(Status) != 0) {

                    throw std::runtime_error("shaderc failed");

                }

                std::ifstream File(OutputPath.ToCString(), std::ios::binary | std::ios::ate);
                if (!File.is_open()) {

                    throw std::runtime_error("Cannot open compiled shader binary");

                }

                uint32_t Size = static_cast<uint32_t>(File.tellg());
                File.seekg(0, std::ios::beg);

                const bgfx::Memory* ShaderMemory = bgfx::alloc(Size);
                File.read(reinterpret_cast<char*>(ShaderMemory->data), Size);

                bgfx::ShaderHandle Handle = bgfx::createShader(ShaderMemory);

                if (IsFragment) {

                    FragmentShaderHandle = Handle;

                } else {

                    VertexShaderHandle = Handle;

                }

            }

            if (!bgfx::isValid(VertexShaderHandle) || !bgfx::isValid(FragmentShaderHandle)) {

                throw std::runtime_error("Program is missing a vertex or fragment shader");

            }

            this->ProgramHandle = bgfx::createProgram(VertexShaderHandle, FragmentShaderHandle, true);

        }

        bgfx::ProgramHandle m_ShaderProgram::UseProgram() {

            return this->ProgramHandle;

        };

    }

}