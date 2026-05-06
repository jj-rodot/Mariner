#include "libraries/m_Vector3.h"

namespace Mariner {

    namespace Libraries {

        m_Vector3* m_Vector3::New(float X, float Y, float Z) {

            m_Vector3* Instance = new m_Vector3();
            Instance->X = X;
            Instance->Y = Y;
            Instance->Z = Z;
            return Instance;

        }

    }

}