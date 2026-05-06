#include "libraries/m_Signal.h"

namespace Mariner {

    namespace Libraries {

        m_Signal* m_Signal::New() {

            m_Signal* Instance = new m_Signal();
            return Instance;

        }

        m_SignalConnection* m_Signal::Connect(m_Function Function) {

            m_SignalConnection* SignalConnection = new m_SignalConnection();
            SignalConnection->Function = Function;

            this->Connections.Add(SignalConnection);
            return SignalConnection;

        }

        m_SignalConnection* m_Signal::Once(m_Function Function) {

            m_SignalConnection* SignalConnection = new m_SignalConnection();
            SignalConnection->Function = Function;
            SignalConnection->ExecuteOnce = true;

            this->Connections.Add(SignalConnection);
            return SignalConnection;

        }

        void m_Signal::Fire() {

            Mariner::Libraries::m_Array<m_SignalConnection*> ConnectionsToRemove = {};

            for(auto Connection : this->Connections) {

                Connection->Function.Call();
                if(Connection->ExecuteOnce) {

                    ConnectionsToRemove.Add(Connection);

                }

            }
            
            for(auto Connection : ConnectionsToRemove) {

                this->Connections.Remove(Connection);

            }

        }

    }

}