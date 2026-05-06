#pragma once

#include "objects/m_Object.h"
#include "libraries/m_String.h"
#include "libraries/m_Content.h"

namespace Mariner {

    namespace Objects {

        struct m_Script : public m_Object {

            public:

                static m_Script* New();

                Mariner::Libraries::m_String Source = "";
                Mariner::Libraries::m_Content* SourceContent = nullptr;

            protected:

                m_Script() = default;
                virtual ~m_Script() = default;

            private:

        };

    }

}