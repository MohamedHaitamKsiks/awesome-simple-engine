#ifndef __ASENGINE_COLUMN_H
#define __ASENGINE_COLUMN_H

#include "Core/Error/Assertion.h"

#include <array>
#include <algorithm>
#include <cstdint>



namespace ASEngine
{
    // column definition used to define matrices
    // stride added
    template <size_t N, size_t Stride>
    class  Column
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

        constexpr inline float& operator[](uint32_t i)
        {
            return m_Data[i];
        }

        constexpr inline float operator[](uint32_t i) const
        {
            return m_Data[i];
        }

    private:
        std::array<float, N + Stride> m_Data;
    };
} // namespace ASEngine


#endif // __ASENGINE_COLUMN_H