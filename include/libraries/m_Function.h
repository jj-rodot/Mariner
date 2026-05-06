#pragma once

#include <functional>
#include <any>

namespace Mariner {

    namespace Libraries {

        struct m_Function { 

            public:

                template<typename FunctionReturn>
                m_Function(FunctionReturn Function) {

                    if constexpr(std::is_same_v<std::invoke_result_t<FunctionReturn>, void>) {

                        this->Function = [Function]() -> std::any {

                            Function();
                            return {};

                        };
                        
                    } else {

                        this->Function = std::function<std::any()>(Function);

                    }

                }

                std::any Call();

                m_Function() = default;
                virtual ~m_Function() = default;

            protected:


            private:

                std::function<std::any()> Function;

        };

    }

}