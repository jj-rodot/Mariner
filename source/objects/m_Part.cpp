#include "objects/m_Part.h"

namespace Mariner {

    namespace Objects {

        m_Part* m_Part::New() {

            m_Part* Instance = new m_Part();
            Instance->Name = "Part";
            Instance->ClassName = "m_Part";
            return Instance;

        }

    }

}