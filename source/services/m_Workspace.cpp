#include "services/m_Workspace.h"

namespace Mariner {

    namespace Services {

        m_Workspace* m_Workspace::New() {

            static m_Workspace* Instance = new m_Workspace();
            Instance->Name = "Workspace";
            Instance->ClassName = "m_Workspace";
            return Instance;

        }

    }

}