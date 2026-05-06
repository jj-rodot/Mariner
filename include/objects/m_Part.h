#pragma once

#include "bgfx/bgfx.h"
#include "objects/m_Object.h"

#include "libraries/m_Color.h"
#include "libraries/m_Vector3.h"

namespace Mariner {

    namespace Objects {

        struct m_Part : public m_Object {

            public:

                static m_Part* New();

                Mariner::Libraries::m_Color* Color = Mariner::Libraries::m_Color::New(0.3, 0.3, 0.3);
                Mariner::Libraries::m_Vector3* Position = Mariner::Libraries::m_Vector3::New(0, 0, 0);

                float Vertecies[9] = {

                    0.0f,  0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                    -0.5f, -0.5f, 0.0f

                };

                uint16_t Fragments[3] = { 0, 2, 1 };

                bgfx::VertexBufferHandle VertexBuffer;
                bgfx::IndexBufferHandle FragmentBuffer;

            protected:

                m_Part() = default;
                virtual ~m_Part() = default;

            private:

        };

    }

}