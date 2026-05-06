#include <chrono>

#include "objects/m_Thread.h"
#include "services/m_TaskScheduler.h"

namespace Mariner {

    namespace Services {

        m_TaskScheduler* m_TaskScheduler::New() {

            static m_TaskScheduler* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_TaskScheduler();
                    Instance->Name = "Task Scheduler";
                    Instance->ClassName = "m_TaskScheduler";

                }

            return Instance;

        }

        void m_TaskScheduler::AddTask(Mariner::Objects::m_Task* Task) {

            this->Tasks.Add(Task);

        }

        void m_TaskScheduler::RemoveTask(Mariner::Objects::m_Task* Task) {

            this->Tasks.Remove(Task);

        } 

        void m_TaskScheduler::Start() {

            auto Thread = Mariner::Objects::m_Thread::New();
            Thread->Name = "m_Worker::A";

            this->IsRunning = true;
            while(this->IsRunning) {

                Mariner::Libraries::m_Array<Mariner::Objects::m_Task*> CyclicTasks = {};

                auto TasksSnapshot = this->Tasks; 
                for(auto Task : TasksSnapshot) {

                    if(!Task->Disabled) {

                        if(Task->OnMainThread) {

                            Task->Execute();

                        } else {

                            Thread->Assign(Task);
                            Thread->Execute();

                        }

                    }

                    if(Task->Cyclic) {

                        CyclicTasks.Add(Task);

                    }
                    
                };

                this->Tasks = CyclicTasks;
                if(this->Tasks.IsEmpty()) {

                    this->Halt();

                }

                std::this_thread::sleep_for(std::chrono::milliseconds(15));

            }

        }

        void m_TaskScheduler::Halt() {

            this->IsRunning = false;

        };
        
    }

}