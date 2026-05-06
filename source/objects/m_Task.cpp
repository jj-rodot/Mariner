#include "objects/m_Task.h"

namespace Mariner {
    
    namespace Objects {

        m_Task* m_Task::New() {

            auto* Instance = new m_Task();
            Instance->Name = "Task";
            Instance->ClassName = "m_Task";
            return Instance;

        }

        void m_Task::Execute() {

            this->TaskState = Mariner::Enums::m_TaskState::RUNNING;
            this->Function.Call();
            this->TaskState = Mariner::Enums::m_TaskState::SLEEPING;

        }

    }

}