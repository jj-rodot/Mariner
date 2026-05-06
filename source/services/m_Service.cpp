#include <services/m_Service.h>

namespace Mariner {

    namespace Services {

        m_Service* m_Service::New() {

            static m_Service* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_Service();
                    Instance->Name = "Service";
                    Instance->ClassName = "m_Service";
                    Instance->m_Initialize();

                }

            return Instance;

        }

    }

}