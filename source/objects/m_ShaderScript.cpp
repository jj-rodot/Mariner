#include "objects/m_ShaderScript.h"

namespace Mariner {

    namespace Objects {

        m_ShaderScript* m_ShaderScript::New() {

            m_ShaderScript* Instance = new m_ShaderScript();
            Instance->Name = "ShaderScript";
            Instance->ClassName = "m_ShaderScript";
            return Instance;

        }

    }

}