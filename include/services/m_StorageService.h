#pragma once

#include "services/m_Service.h"
#include "libraries/m_String.h"
#include "libraries/m_Dictionary.h"

namespace Mariner {

    namespace Services {

        struct m_StorageService : public m_Service {

            public:

                static m_StorageService* New();

                void Store(Mariner::Libraries::m_String Name, void* Data);
                void* Load(Mariner::Libraries::m_String Name);

                void StoreInternal(Mariner::Libraries::m_String Name, void* Data);
                void* LoadInternal(Mariner::Libraries::m_String Name);

            protected:

                m_StorageService() = default;
                virtual ~m_StorageService() = default;

            private:

                Mariner::Libraries::m_Dictionary<Mariner::Libraries::m_String, void*> Data = {};
                Mariner::Libraries::m_Dictionary<Mariner::Libraries::m_String, void*> InternalData = {};

        };

    }
    
}