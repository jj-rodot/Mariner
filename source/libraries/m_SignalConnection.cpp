#include "libraries/m_SignalConnection.h"

namespace Mariner {

    namespace Libraries {

        m_SignalConnection* m_SignalConnection::New() {

            m_SignalConnection* Instance = new m_SignalConnection();
            return Instance;

        }

    }

}