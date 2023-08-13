#ifndef ASENGINE_DYNAMIC_ARRAY_H
#define ASENGINE_DYNAMIC_ARRAY_H

#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cstring>

#define DYNAMIC_ARRAY_GROWTH_FACTOR 2

namespace ASEngine
{
    //interface for dynamic array
    class DynamicArray
    {
        public:
            // add new element to dynamic array with no value
            virtual size_t Add() = 0;
            
            // reserve space for dynamic array
            virtual void Reserve(size_t size) = 0;

            // remove index
            virtual void Remove(size_t index) = 0;

            // get ptr at
            virtual void* PtrAt(size_t index) = 0;

            // clear 
            virtual void Clear() = 0;

            // get size
            virtual size_t GetSize() = 0;

            // get capacity
            virtual size_t GetCapacity() = 0;
    };

    // dynamic array grow at need and memory safe, it's based on std vector
    template <typename T>
    class TDynamicArray: public DynamicArray
    {
        public:
            // create empty dybamic array
            TDynamicArray() {};
            // create dynamic array with preallocated capacity
            TDynamicArray(size_t capacity)
            {
                Reserve(capacity);
            }

            // get data
            inline T* GetData()
            {
                return m_Data.data();
            }

            // add new element to dynamic array with no value
            size_t Add()
            {
                T t{};
                m_Data.push_back(t);
                return m_Data.size() - 1;
            }

            void *PtrAt(size_t index)
            {
                return (void*) (m_Data.data() + index);
            }

            // Push element to dynamic array
            inline size_t Push(const T& value)
            {
                m_Data.push_back(value);
                return m_Data.size() - 1;
            }
            
            // pop last element
            inline T Pop()
            {
                T value = m_Data[m_Data.size() - 1];
                m_Data.pop_back();
                return value;
            }

            // reserve space for dynamic array
            inline void Reserve(size_t size)
            {
                m_Data.reserve(size);
            }

            // remove index
            inline void Remove(size_t index)
            {
                m_Data.erase(m_Data.cbegin() + index);
            }

            // clear
            inline void Clear()
            {
                m_Data.clear();
            };

            // get size
            size_t GetSize()
            {
                return m_Data.size();
            }

            // get capacity
            size_t GetCapacity()
            {
                return m_Data.capacity();
            }

            // get value at
            inline T& operator[](size_t index)
            {
                return m_Data[index];
            };

            // iterator
            using Iterator = class DynamicArrayIterator
            {
            public:
                DynamicArrayIterator(TDynamicArray<T>* array, size_t index)
                {
                    m_Array = array;
                    m_Index = index;
                }

                inline size_t GetIndex() const { return m_Index; };

                inline DynamicArrayIterator operator++(int)
                {
                    m_Index++;
                    return *this;
                };

                inline DynamicArrayIterator operator++()
                {
                    m_Index++;
                    return *this;
                };

                inline T &operator*(void) const
                {
                    return m_Array->m_Data[m_Index];
                };

                inline bool operator==(const DynamicArrayIterator &it) const
                {
                    return m_Index == it.m_Index;
                };

                inline bool operator!=(const DynamicArrayIterator &it) const
                {
                    return m_Index != it.m_Index;
                };

            private:
                TDynamicArray<T>* m_Array = nullptr;
                size_t m_Index;
            };

            // iterator begin
            inline Iterator begin()
            {
                return Iterator(this, 0);
            };
            // iterator end
            inline Iterator end()
            {
                return Iterator(this, m_Data.size());
            };

        private:
            std::vector<T> m_Data;

    };
} // namespace ASEngine

#endif // ASENGINE_DYNAMIC_ARRAY_H