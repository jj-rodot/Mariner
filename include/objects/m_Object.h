#pragma once

#include "libraries/m_Array.h"
#include "libraries/m_String.h"

namespace Mariner {

    namespace Objects {

        struct m_Object {

            public:
            
                static m_Object* New();

                Mariner::Libraries::m_String Name = "";
                Mariner::Libraries::m_String ClassName = "";
                m_Object* Parent;

                Mariner::Libraries::m_Array<m_Object*> GetChildren();
                
                void SetParent(m_Object* Other);
                size_t GetMemoryUsage();

            protected:
            
                m_Object() = default;
                virtual ~m_Object() = default;

                virtual void m_Initialize();

            private:
                Mariner::Libraries::m_Array<m_Object*> Children = {};

        };

    }

}