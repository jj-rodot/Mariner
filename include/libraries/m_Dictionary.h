#pragma once

#include <vector>
#include <initializer_list>

namespace Mariner {

    namespace Libraries {

        template<typename K, typename V>
        struct m_Dictionary {

            public:

                m_Dictionary(std::initializer_list<std::pair<K, V>> Dictionary) {

                    this->InternalDictionary = Dictionary;

                }

                m_Dictionary(const m_Dictionary& Other) {

                    this->InternalDictionary = Other.InternalDictionary;

                }

                void Add(K Key, V Value) {

                    this->InternalDictionary.emplace_back(Key, Value);

                }

                void Remove(K Key) {

                    InternalDictionary.erase(

                        std::remove_if(InternalDictionary.begin(), InternalDictionary.end(),
                        [&Key](const std::pair<K,V>& p) { return p.first == Key; }),
                        InternalDictionary.end()

                    );

                }

                void Clear() {

                    this->InternalDictionary.clear();

                }

                void operator=(m_Dictionary<K, V> Other) {

                    this->InternalDictionary = Other;

                }

                bool operator==(m_Dictionary<K, V> Other) {

                    return this->InternalDictionary == Other.InternalDictionary;

                }

                std::pair<K, V>& operator[](size_t Index) {

                    return InternalDictionary.at(Index);

                }

                std::pair<K, V>& operator[](size_t Index) const {

                    return InternalDictionary.at(Index);

                }

                auto begin() {

                    return this->InternalDictionary.data();

                }

                auto end() {

                    return this->InternalDictionary.data() + this->InternalDictionary.size();

                }

                auto begin() const {

                    return this->InternalDictionary.data();

                }

                auto end() const {

                    return this->InternalDictionary.data() + this->InternalDictionary.size();

                }

                virtual ~m_Dictionary() = default;

            protected:

            private:

                std::vector<std::pair<K, V>> InternalDictionary = {};

        };

    }

}