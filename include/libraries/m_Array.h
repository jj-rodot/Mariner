#pragma once

#include <vector>
#include <initializer_list>

namespace Mariner {

    namespace Libraries {

        template<typename T>
        struct m_Array {

            public:

                m_Array(std::initializer_list<T> Array) {

                    this->InternalArray = Array;

                }

                m_Array(const m_Array& Other) {

                    this->InternalArray = Other.InternalArray;

                }

                void Add(T Element) {

                    this->InternalArray.push_back(Element);

                }

                void Remove(T Element) {

                    InternalArray.erase(

                        std::remove(InternalArray.begin(), InternalArray.end(), Element),
                        InternalArray.end()

                    );

                }

                bool IsEmpty() {

                    return this->InternalArray.empty();

                }

                void Clear() {

                    this->InternalArray.clear();

                }

                void operator=(m_Array<T> Other) {

                    this->InternalArray = Other.InternalArray;

                }

                bool operator==(m_Array<T> Other) {

                    return this->InternalArray == Other.InternalArray;

                }

                T& operator[](size_t Index) {

                    return InternalArray.at(Index);

                }

                const T& operator[](size_t Index) const {

                    return InternalArray.at(Index);

                }

                T* begin() {

                    return this->InternalArray.data();

                }

                T* end() {

                    return this->InternalArray.data() + this->InternalArray.size();

                }

                const T* begin() const {

                    return this->InternalArray.data();

                }

                const T* end() const {

                    return this->InternalArray.data() + this->InternalArray.size();

                }

                virtual ~m_Array() = default;

            protected:

            private:

                std::vector<T> InternalArray = {};

        };

    }

}