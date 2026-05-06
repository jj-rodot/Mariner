#pragma once

#include "GLFW/glfw3.h"
#include "objects/m_Object.h"
#include "libraries/m_String.h"

namespace Mariner {

    namespace Objects {

        struct m_Window : public m_Object {

            public:

                static m_Window* New();

                uint16_t Width = 0;
                uint16_t Height = 0;

                void CreateWindow();

            protected:

                m_Window() = default; 
                virtual ~m_Window() = default;

            private:

                GLFWwindow* WindowHandle;

        };

    }

}