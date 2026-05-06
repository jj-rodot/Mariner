#include <libraries/m_String.h>

namespace Mariner {

    namespace Libraries {

        m_String::m_String(const char* CString) {

            this->InternalString = CString;

        }

        const char* m_String::ToCString() {

            return this->InternalString.c_str();

        }

        void m_String::operator=(const char* OtherString) {

            this->InternalString = OtherString;

        }

        void m_String::operator=(m_String OtherString) {

            this->InternalString = OtherString.ToCString();

        }

        bool m_String::operator==(const char* OtherString) {

            return this->InternalString == OtherString;

        }

        bool m_String::operator==(m_String OtherString) {

            return this->InternalString == OtherString.InternalString;

        }

        m_String m_String::operator+(const char* OtherString) {

            return m_String((this->InternalString + OtherString).c_str());


        }

        m_String m_String::operator+(m_String OtherString) {

            return m_String((this->InternalString + OtherString.ToCString()).c_str());

        }

    }

}