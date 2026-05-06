#pragma once

#include "objects/m_Object.h"

namespace Mariner {

    namespace Objects {

        struct m_Camera : public m_Object {

            public:

                static m_Camera* New();

                void StartRendering();
                void StopRendering();

            protected:

                m_Camera() = default;
                virtual ~m_Camera() = default;

            private:

        };

    }

}