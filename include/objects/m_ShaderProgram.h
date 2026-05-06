#pragma once

#include "bgfx/bgfx.h"
#include "libraries/m_Array.h"

#include "objects/m_Program.h"
#include "objects/m_ShaderScript.h"

namespace Mariner {

    namespace Objects {

        struct m_ShaderProgram : public m_Program {

            public:

                static m_ShaderProgram* New();

                void AddShader(m_ShaderScript* Script);
                void RemoveShader(m_ShaderScript* Script);

                void Compile();
                bgfx::ProgramHandle UseProgram();

            protected:

                m_ShaderProgram() = default;
                virtual ~m_ShaderProgram() = default;

            private:

                Mariner::Libraries::m_Array<m_ShaderScript*> LinkedScripts = {};
                bgfx::ProgramHandle ProgramHandle = BGFX_INVALID_HANDLE;

        };

    }

}