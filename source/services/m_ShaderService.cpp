#include <services/m_ShaderService.h>

namespace Mariner {

    namespace Services {

        m_ShaderService* m_ShaderService::New() {

            static m_ShaderService* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_ShaderService();
                    Instance->Name = "ShaderService";
                    Instance->ClassName = "m_ShaderService";
                    Instance->m_Initialize();

                }

            return Instance;

        }

    }

}