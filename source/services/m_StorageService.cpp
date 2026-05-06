#include "services/m_StorageService.h"

namespace Mariner {

    namespace Services {

        m_StorageService* m_StorageService::New() {

            static m_StorageService* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_StorageService();
                    Instance->Name = "Storage Service";
                    Instance->ClassName = "m_StorageService";

                }

            return Instance;

        }

        void m_StorageService::Store(Mariner::Libraries::m_String Name, void* Data) {

            this->Data.Add(Name, Data);

        };

        void* m_StorageService::Load(Mariner::Libraries::m_String Name) {

            for(auto [Key, Data] : this->Data) {

                if(Key == Name) {

                    return Data;

                };

            } 

            return nullptr;

        };

        void m_StorageService::StoreInternal(Mariner::Libraries::m_String Name, void* Data) {

            this->InternalData.Add(Name, Data);

        };

        void* m_StorageService::LoadInternal(Mariner::Libraries::m_String Name) {

            for(auto [Key, Data] : this->InternalData) {

                if(Key == Name) {

                    return Data;

                };

            } 

            return nullptr;

        };

    }

}