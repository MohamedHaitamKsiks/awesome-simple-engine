#ifndef __ASENGINE_MATRIX_H
#define __ASENGINE_MATRIX_H

#include <cstdint>
#include "Column.h"
#include "API/API.h"

namespace ASEngine
{
    // define template for column-major matrix
    // The matrix is define by it's dimentions + a stride added to each column
    template <size_t Cols, size_t Rows, size_t Stride>
    class ASENGINE_API Matrix
    {
    protected:
        using ColumnType = Column<Rows, Stride>;
        using DataType = std::array<ColumnType, Cols>;

    public:
        constexpr Matrix() = default;
        constexpr Matrix(const Matrix& matrix) = default;

        constexpr Matrix(const DataType& cols) : m_Cols(cols)
        {
        }

        // access data
        constexpr inline ColumnType& operator[](uint32_t i)
        {
            return m_Cols[i];
        }

        constexpr inline const ColumnType &operator[](uint32_t i) const
        {
            return m_Cols[i];
        }

        // get coulmn size
        constexpr static inline uint32_t GetColumnsSize()
        {
            return static_cast<uint32_t>(Cols);
        }

        // get row size
        constexpr static inline uint32_t GetRowsSize()
        {
            return static_cast<uint32_t>(Rows);
        }

        // matrix multiplication
        template <size_t Cols_B>
        inline constexpr static void Multiply(const Matrix &a, const Matrix<Cols_B, Cols, Stride> &b,  Matrix<Cols_B, Rows, Stride>& result)
        {
            for (size_t j = 0; j < Rows; j++)
            {
                for (size_t i = 0; i < Cols_B; i++)
                {
                    float tmp = 0.0f;
                    for (size_t k = 0; k < Cols; k++)
                    {
                        tmp += a[k][j] * b[i][k];
                    }
                    result[i][j] = tmp;
                }
            }
        }

        // matrix multiplication
        template <size_t Cols_B>
        inline friend constexpr Matrix<Cols_B, Rows, Stride> operator*(const Matrix &a, const Matrix<Cols_B, Cols, Stride> &b)
        {
            Matrix<Cols_B, Rows, Stride> result;
            Matrix::Multiply(a, b, result);

            return result;
        }

        // addition
        friend constexpr Matrix operator+(const Matrix &a, const Matrix &b)
        {
            Matrix result;
            for (size_t j = 0; j < Rows; j++)
            {
                for (size_t i = 0; i < Cols; i++)
                {
                    result[i][j] = a[i][j] + b[i][j];
                }
            }
            return result;
        }

        // substraction
        friend constexpr Matrix operator-(const Matrix &a, const Matrix &b)
        {
            Matrix result;
            for (size_t j = 0; j < Rows; j++)
            {
                for (size_t i = 0; i < Cols; i++)
                {
                    result[i][j] = a[i][j] - b[i][j];
                }
            }
            return result;
        }

        // scale
        friend constexpr Matrix operator*(const Matrix &matrix, float s)
        {
            Matrix result;
            for (size_t j = 0; j < Rows; j++)
            {
                for (size_t i = 0; i < Cols; i++)
                {
                    result[i][j] =  matrix[i][j] * s;
                }
            }
            return result;
        }

    private:
        DataType m_Cols;
    };
} // namespace ASEngine


#endif // __ASENGINE_MATRIX_H
