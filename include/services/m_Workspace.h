#pragma once

#include "services/m_Service.h"

namespace Mariner {

    namespace Services {

        struct m_Workspace : public m_Service {

            public:

                static m_Workspace* New();

            protected:

                m_Workspace() = default;
                virtual ~m_Workspace() = default;

            private:

        };

    }

}