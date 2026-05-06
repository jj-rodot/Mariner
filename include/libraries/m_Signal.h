#pragma once

#include "libraries/m_Array.h"
#include "libraries/m_Function.h"
#include "libraries/m_SignalConnection.h"

namespace Mariner {

    namespace Libraries {

        struct m_Signal {

            public:

                static m_Signal* New();

                int NumberOfConnections = 0;

                void Fire();

                m_SignalConnection* Connect(m_Function Function);
                m_SignalConnection* Once(m_Function Function);

            protected:

            private:

                m_Array<m_SignalConnection*> Connections = {};

        };

    }

}