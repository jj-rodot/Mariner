#include "objects/m_Program.h"

namespace Mariner {

    namespace Objects {

        m_Program* m_Program::New() {

            m_Program* Instance = new m_Program();
            Instance->Name = "Program";
            Instance->ClassName = "m_Program";
            return Instance;

        }

    }

}