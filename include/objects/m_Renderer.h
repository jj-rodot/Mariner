#pragma once

#include "objects/m_Part.h"
#include "objects/m_Object.h"
#include "libraries/m_Array.h"
#include "enums/m_RenderType.h"

namespace Mariner {

    namespace Objects {

        struct m_Renderer : public m_Object {

            public:

                static m_Renderer* New();

                Mariner::Enums::m_RenderType RenderType = Mariner::Enums::m_RenderType::METAL;

                void AddPartToRender(m_Part* PartToRender);
                void RemovePartToRender(m_Part* PartToStopRendering);

                Mariner::Libraries::m_String GetShaderLanguageType();
                void StartRenderer();

            protected:

                m_Renderer() = default; 
                virtual ~m_Renderer() = default; 

            private:

                Mariner::Libraries::m_Array<m_Part*> PartsToRender = {};

        };

    }

}