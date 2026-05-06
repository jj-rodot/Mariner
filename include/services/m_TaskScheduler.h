#pragma once

#include "objects/m_Task.h"
#include "services/m_Service.h"
#include "libraries/m_Array.h"
#include "enums/m_TaskCategory.h"
#include "enums/m_TaskPriority.h"

namespace Mariner {

    namespace Services {

        struct m_TaskScheduler : public m_Service {

            public:

                static m_TaskScheduler* New();

                void AddTask(Mariner::Objects::m_Task* Task);
                void RemoveTask(Mariner::Objects::m_Task* Task);

                void Start();
                void Halt();

            protected:

                m_TaskScheduler() = default;
                virtual ~m_TaskScheduler() = default;

            private:

                bool IsRunning = false;
                Mariner::Libraries::m_Array<Mariner::Objects::m_Task*> Tasks = {};

        };

    }

}