#pragma once

#include "objects/m_Script.h"
#include "enums/m_ShaderType.h"

namespace Mariner {

    namespace Objects {

        struct m_ShaderScript : public m_Script {

            public:

                static m_ShaderScript* New();

                Mariner::Enums::m_ShaderType ShaderType = Mariner::Enums::m_ShaderType::VERTEX;

            protected:

                m_ShaderScript() = default;
                virtual ~m_ShaderScript() = default;

            private:

        };

    }

}