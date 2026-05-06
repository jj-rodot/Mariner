#pragma once

#include "objects/m_Object.h"
#include "libraries/m_String.h"

namespace Mariner {

    namespace Objects {

        struct m_Program : public m_Object {

            public:

                static m_Program* New();

            protected:

                m_Program() = default;
                virtual ~m_Program() = default;

            private:

        };

    }

}