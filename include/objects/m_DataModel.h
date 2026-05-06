#pragma once

#include "objects/m_Object.h"

namespace Mariner {

    namespace Objects {

        struct m_DataModel : public m_Object {

            public:
            
                static m_DataModel* New();

            protected:

                m_DataModel() = default;
                virtual ~m_DataModel() = default;

            private:
            
        };

    }

}