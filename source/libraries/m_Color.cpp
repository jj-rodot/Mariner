#include "libraries/m_Color.h"

namespace Mariner {

    namespace Libraries {

        m_Color* m_Color::New(float R, float G, float B) {

            m_Color* Instance = new m_Color();
            Instance->R = R;
            Instance->G = G;
            Instance->B = B;
            return Instance;

        }

        m_Color* m_Color::FromRGB(float R, float G, float B) {

            m_Color* Instance = new m_Color();
            Instance->R = R / 255.0f;
            Instance->G = G / 255.0f;
            Instance->B = B / 255.0f;
            return Instance;

        }

    }

}