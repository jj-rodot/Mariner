#pragma once

#include "objects/m_Object.h"
#include "libraries/m_Function.h"

#include "enums/m_TaskState.h"
#include "enums/m_TaskCategory.h"
#include "enums/m_TaskPriority.h"

namespace Mariner {

    namespace Objects {

        struct m_Task : public m_Object {

            public:

                static m_Task* New();

                bool Cyclic = false;
                bool Disabled = false;
                bool OnMainThread = false;

                Mariner::Libraries::m_Function Function;

                Mariner::Enums::m_TaskState TaskState = Mariner::Enums::m_TaskState::SLEEPING;
                Mariner::Enums::m_TaskCategory TaskCategory = Mariner::Enums::m_TaskCategory::GENERAL;
                Mariner::Enums::m_TaskPriority m_TaskPriority = Mariner::Enums::m_TaskPriority::MEDIUM;

                void Execute();

            protected:

                m_Task() = default;
                virtual ~m_Task() = default;

            private:

        };

    }

}