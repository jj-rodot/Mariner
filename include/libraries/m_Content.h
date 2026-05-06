#pragma once

#include "objects/m_Object.h"
#include "libraries/m_String.h"

namespace Mariner {

    namespace Libraries {

        struct m_Content {

            public:

                static m_Content* FromDirectory(Mariner::Libraries::m_String String);
                static m_Content* FromObject(Mariner::Objects::m_Object* Object);

                Mariner::Libraries::m_String Directory = "";
                Mariner::Objects::m_Object* Object = nullptr;

            protected:

            private:

        };

    }

}