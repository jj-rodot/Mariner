#pragma once

#include "libraries/m_Array.h"
#include "libraries/m_Function.h"

namespace Mariner {

    namespace Libraries {

        struct m_SignalConnection {

            public:

                static m_SignalConnection* New();

                bool ExecuteOnce = false;
                m_Function Function;    
                
            protected:

            private:

        };

    }

}