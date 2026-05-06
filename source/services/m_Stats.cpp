#include "services/m_Stats.h"

namespace Mariner {

    namespace Services {

        m_Stats* m_Stats::New() {

            static m_Stats* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_Stats();
                    Instance->Name = "Stats";
                    Instance->ClassName = "m_Stats";

                }

            return Instance;

        }

        void m_Stats::IncrementTotalObjectAllocations() {

            this->TotalObjectAllocations += 1;

        }

        void m_Stats::DecrementTotalObjectAllocations() {

            this->TotalObjectAllocations -= 1;

        }

        void m_Stats::IncrementTotalObjectMemoryAllocated(size_t Size) {

            this->TotalObjectMemoryAllocated += Size;

        }

        void m_Stats::DecrementTotalObjectMemoryAllocated(size_t Size) {

            this->TotalObjectMemoryAllocated -= Size;

        }

    }

}