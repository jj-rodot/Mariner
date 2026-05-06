#include "objects/m_Part.h"
#include "objects/m_Camera.h"
#include "objects/m_Renderer.h"

namespace Mariner {

    namespace Objects {

        m_Camera* m_Camera::New() {

            static m_Camera* Instance = new m_Camera();
            Instance->Name = "Camera";
            Instance->ClassName = "m_Camera";
            return Instance;

        }

        void m_Camera::StartRendering() {

            auto Renderer = m_Renderer::New();
            Renderer->StartRenderer();
            
            auto Part = m_Part::New();
            Renderer->AddPartToRender(Part);

        }

    }

}