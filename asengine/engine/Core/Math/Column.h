#ifndef ASENGINE_COLUMN_H
#define ASENGINE_COLUMN_H

#include "Core/Error/Assertion.h"

#include <array>
#include <algorithm>
#include <cstdint>

namespace ASEngine
{
    // column definition used to define matrices
    // stride added 
    template <size_t N , size_t Stride>
    class Column
    {
    public:
        constexpr Column() = default;
        constexpr Column(const Column& column) = default;

        constexpr Column(const std::array<float, N + Stride>& data): m_Data(data)
        {
        }
        
        /*Column(const std::array<float, N> &data)
        {
            std::copy(data.begin(), data.end(), m_Data.begin());
        }
        */

        constexpr inline float& operator[](int i)
        {
            ASENGINE_ASSERT(i < N && i >= 0, "Invalid index");
            return m_Data[i];
        }

        constexpr inline float operator[](int i) const
        {
            ASENGINE_ASSERT(i < N && i >= 0, "Invalid index");
            return m_Data[i];
        }

    private:
        std::array<float, N + Stride> m_Data;
    };
} // namespace ASEngine


#endif // ASENGINE_COLUMN_H