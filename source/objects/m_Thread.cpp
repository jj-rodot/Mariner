#include "objects/m_Thread.h"

namespace Mariner {
    
    namespace Objects {

        m_Thread* m_Thread::New() {

            auto* Instance = new m_Thread();
            Instance->Name = "Thread";
            Instance->ClassName = "m_Thread";
            return Instance;

        }

        void m_Thread::Assign(m_Task* Task) {

            this->AssignedTask = Task;

        }

        void m_Thread::Execute() {

            std::thread([this](){

                pthread_setname_np(this->Name.ToCString());

                if(this->AssignedTask) {

                    this->AssignedTask->Execute();

                } else {

                    return;

                }

            }).join();

        }

    }

}