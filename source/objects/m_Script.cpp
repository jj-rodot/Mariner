#include "objects/m_ShaderScript.h"

namespace Mariner {

    namespace Objects {

        m_Script* m_Script::New() {

            m_Script* Instance = new m_Script();
            Instance->Name = "Script";
            Instance->ClassName = "m_Script";
            return Instance;

        }

    }

}