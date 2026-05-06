#pragma once

namespace Mariner {

    namespace Libraries {

        struct m_Vector3 {

            public:

                static m_Vector3* New(float X, float Y, float Z);

                float X = 0.0;
                float Y = 0.0;
                float Z = 0.0;

            protected:

            private:

        };

    }

}