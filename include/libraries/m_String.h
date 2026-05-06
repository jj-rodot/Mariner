#pragma once

#include <string>

namespace Mariner {

    namespace Libraries {

        struct m_String {

            public:

                m_String(const char* CString);

                void operator=(const char* OtherString);
                void operator=(m_String OtherString);

                bool operator==(const char* OtherString);
                bool operator==(m_String OtherString);

                m_String operator+(const char* OtherString);
                m_String operator+(m_String OtherString);

                const char* ToCString();

                m_String() = default;
                virtual ~m_String() = default;

            protected:

            private:

                std::string InternalString = "";

        };

    }

}