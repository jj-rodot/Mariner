#pragma once

#include "services/m_Service.h"

namespace Mariner {

    namespace Services {

        struct m_Stats : public m_Service {

            public:

                static m_Stats* New();
                
                size_t TotalObjectAllocations = 0;
                size_t TotalObjectMemoryAllocated = 0;

                void IncrementTotalObjectAllocations();
                void DecrementTotalObjectAllocations();

                void IncrementTotalObjectMemoryAllocated(size_t Size);
                void DecrementTotalObjectMemoryAllocated(size_t Size);

            protected:

                m_Stats() = default;
                virtual ~m_Stats() = default;

            private:


        };

    }

}