#pragma once

#include "services/m_Service.h"

#include "objects/m_ShaderScript.h"
#include "objects/m_ShaderProgram.h"

namespace Mariner {

    namespace Services {

        struct m_ShaderService : public m_Service {

            public:

                static m_ShaderService* New();

            protected:

                m_ShaderService() = default;
                virtual ~m_ShaderService() = default;

            private:

        };

    }

}