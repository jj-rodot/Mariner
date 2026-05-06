#pragma once

namespace Mariner {

    namespace Libraries {

        struct m_Color {

            public:

                static m_Color* New(float R, float G, float B);
                static m_Color* FromRGB(float R, float G, float B);

                float R = 0.0;
                float G = 0.0;
                float B = 0.0;

            protected:

            private:

        };

    }

}