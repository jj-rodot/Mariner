#define GLFW_EXPOSE_NATIVE_COCOA

#include "bx/math.h"
#include "bgfx/bgfx.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "objects/m_Window.h"
#include "objects/m_Renderer.h"
#include "objects/m_ShaderScript.h"
#include "objects/m_ShaderProgram.h"

#include "libraries/m_Function.h"

#include "services/m_RunService.h"
#include "services/m_StorageService.h"

namespace Mariner {

    namespace Objects {

        m_Renderer* m_Renderer::New() {

            static m_Renderer* Instance = new m_Renderer();
            Instance->Name = "Renderer";
            Instance->ClassName = "m_Renderer";
            return Instance;

        }

        Mariner::Libraries::m_String m_Renderer::GetShaderLanguageType() {

            if(this->RenderType == Mariner::Enums::m_RenderType::DIRECTX) {

                return Mariner::Libraries::m_String("s_5_0");

            } else if(this->RenderType == Mariner::Enums::m_RenderType::METAL) {

                return Mariner::Libraries::m_String("metal");

            } else if(this->RenderType == Mariner::Enums::m_RenderType::OPENGL) {

               return Mariner::Libraries::m_String("150");

            } else {

                return Mariner::Libraries::m_String("spirv");

            }

        }

        void m_Renderer::StartRenderer() {
            
            auto RunService = Mariner::Services::m_RunService::New();
            auto StorageService = Mariner::Services::m_StorageService::New();
            auto CurrentWindow = reinterpret_cast<m_Window*>(StorageService->LoadInternal("m_EngineWindowHandle"));

            bgfx::Init Initialize = {};
            
            if(this->RenderType == Mariner::Enums::m_RenderType::DIRECTX) {

                Initialize.type = bgfx::RendererType::Direct3D11;

            } else if(this->RenderType == Mariner::Enums::m_RenderType::METAL) {

                Initialize.type = bgfx::RendererType::Metal;

            } else if(this->RenderType == Mariner::Enums::m_RenderType::OPENGL) {

                Initialize.type = bgfx::RendererType::OpenGL;

            } else {

                Initialize.type = bgfx::RendererType::Vulkan;

            }

            Initialize.platformData.nwh = glfwGetCocoaWindow(reinterpret_cast<GLFWwindow*>((StorageService->LoadInternal("m_NativeWindowHandle"))));
            Initialize.resolution.reset = BGFX_RESET_VSYNC;
            Initialize.resolution.width = CurrentWindow->Width;
            Initialize.resolution.height = CurrentWindow->Height;

            bgfx::init(Initialize);

            auto FragShader = m_ShaderScript::New();
            FragShader->ShaderType = Mariner::Enums::m_ShaderType::FRAGMENT;
            FragShader->Source = R"(

                #include <bgfx_shader.sh>
                void main() {
                    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
                }

            )";

            auto VertexShader = m_ShaderScript::New();
            VertexShader->ShaderType = Mariner::Enums::m_ShaderType::VERTEX;
            VertexShader->Source = R"(

                $input a_position

                #include <bgfx_shader.sh>

                void main() {

                    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

                }

            )";

            auto ShaderProgram = m_ShaderProgram::New();
            ShaderProgram->AddShader(FragShader);
            ShaderProgram->AddShader(VertexShader);
            ShaderProgram->Compile();

            RunService->PreRender.Connect(Mariner::Libraries::m_Function([this, ShaderProgram]() {

                auto StorageService = Mariner::Services::m_StorageService::New();
                auto CurrentWindow = reinterpret_cast<m_Window*>(StorageService->LoadInternal("m_EngineWindowHandle"));

                bgfx::setViewRect(0, 0, 0, CurrentWindow->Width, CurrentWindow->Height);
                bgfx::setViewClear(0,

                    BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                    0xffffffff, 
                    1.0f,
                    0

                );

                float View[16], Proj[16];
                bx::mtxIdentity(View);
                bx::mtxIdentity(Proj);
                bgfx::setViewTransform(0, View, Proj);

                auto PartsToRender = this->PartsToRender;
                if(!PartsToRender.IsEmpty()) {

                    for(auto Part : PartsToRender) {

                        bgfx::setIndexBuffer(Part->FragmentBuffer);
                        bgfx::setVertexBuffer(0, Part->VertexBuffer);
                        bgfx::setState(BGFX_STATE_DEFAULT);
                        bgfx::submit(0, ShaderProgram->UseProgram());

                    }

                }

                bgfx::touch(0);
                bgfx::frame();

            }));

        };

        void m_Renderer::AddPartToRender(m_Part* PartToRender) {
        
            bgfx::VertexLayout Layout;
            Layout.begin();
            Layout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
            Layout.end();

            PartToRender->VertexBuffer = bgfx::createVertexBuffer(

                bgfx::makeRef(PartToRender->Vertecies, sizeof(PartToRender->Vertecies)), Layout

            );

            PartToRender->FragmentBuffer = bgfx::createIndexBuffer(

                bgfx::makeRef(PartToRender->Fragments, sizeof(PartToRender->Fragments))

            );

            this->PartsToRender.Add(PartToRender);

        };

        void m_Renderer::RemovePartToRender(m_Part* PartToStopRendering) {

            this->PartsToRender.Remove(PartToStopRendering);

        };

    }

}