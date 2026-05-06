#include <objects/m_Object.h>

namespace Mariner {

    namespace Objects {

        m_Object *m_Object::New() {

            auto *Instance = new m_Object();
            Instance->Name = "Object";
            Instance->ClassName = "m_Object";
            return Instance;
        }

        void m_Object::m_Initialize() {


        };

        size_t m_Object::GetMemoryUsage() {

            return sizeof(*this);

        }

        Mariner::Libraries::m_Array<m_Object *> m_Object::GetChildren() {

            return this->Children;

        };

        void m_Object::SetParent(m_Object *OtherParent) {

            if (OtherParent) {

                if (OtherParent != this) {

                    if (this->Parent) {

                        this->Parent->Children.Remove(this);

                        OtherParent->Children.Add(this);
                        this->Parent = OtherParent;

                    } else {

                        OtherParent->Children.Add(this);
                        this->Parent = OtherParent;
                    }

                } else {

                    throw std::runtime_error("Cannot parent an object to itself!");

                }

            } else {

                return;
            }

        };

    }

}