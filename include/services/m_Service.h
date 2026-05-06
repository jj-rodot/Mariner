#pragma once

#include <objects/m_Object.h>

namespace Mariner {

    namespace Services {

        struct m_Service : public Mariner::Objects::m_Object {

            public:

                static m_Service* New();

            protected:

                m_Service() = default;
                virtual ~m_Service() = default;

            private:

        };

    }

}