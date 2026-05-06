#pragma once

#include <thread>

#include "objects/m_Object.h"
#include "objects/m_Task.h"

namespace Mariner {

    namespace Objects {

        struct m_Thread : public m_Object {

            public:

                static m_Thread* New();

                bool Disabled = false;

                void Assign(m_Task* Task);
                void Execute();

            protected:

                m_Thread() = default;
                virtual ~m_Thread() = default;

            private:

                m_Task* AssignedTask = nullptr;

        };

    }

}