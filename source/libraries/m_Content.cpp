#include "libraries/m_Content.h"

namespace Mariner {

    namespace Libraries {

        m_Content* m_Content::FromDirectory(Mariner::Libraries::m_String String) {

            m_Content* Instance = new m_Content();
            Instance->Directory = String;
            return Instance;

        }

        m_Content* m_Content::FromObject(Mariner::Objects::m_Object* Object) { 

            m_Content* Instance = new m_Content();
            Instance->Object = Object;
            return Instance;

        }

    }

}