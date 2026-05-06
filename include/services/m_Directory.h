#include "services/m_Service.h"
#include "libraries/m_String.h"

namespace Mariner {

    namespace Services {

        struct m_Directory : public m_Service {

            public:

                static m_Directory* New();

                Mariner::Libraries::m_String GetContentDirectory();
                Mariner::Libraries::m_String GetVendoredDirectory();

            protected:

                m_Directory() = default;
                virtual ~m_Directory() = default;

            private:

        };

    }

}