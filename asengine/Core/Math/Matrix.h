#ifndef ASENGINE_MATRIX_H
#define ASENGINE_MATRIX_H

#include <cstdint>
#include "Column.h"

namespace ASEngine
{
    // define template for column-major matrix 
    // The matrix is define by it's dimentions + a stride added to each column
    template <size_t Cols, size_t Rows, size_t Stride>
    class Matrix
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
        constexpr inline ColumnType& operator[](int i)
        {
            ASENGINE_ASSERT(i < Cols && i >= 0, "Invalid index");
            return m_Cols[i];
        }

        constexpr inline const ColumnType &operator[](int i) const
        {
            ASENGINE_ASSERT(i < Cols && i >= 0, "Invalid index");
            return m_Cols[i];
        }

        // matrix multiplication (naive implementation)
        template <size_t Cols_B>
        friend constexpr Matrix<Cols_B, Rows, Stride> operator*(const Matrix &a, const Matrix<Cols_B, Cols, Stride> &b)
        {
            Matrix<Cols_B, Rows, Stride> result;
            for (int j = 0; j < Rows; j++)
            {
                for (int i = 0; i < Cols_B; i++)
                {
                    result[i][j] = 0.0f;
                    for (int k = 0; k < Cols; k++)
                    {
                        result[i][j] += a[k][j] + b[i][k];
                    }
                }
            }

            return result;
        }

        // addition
        friend constexpr Matrix operator+(const Matrix &a, const Matrix &b)
        {
            Matrix result;
            for (int j = 0; j < Rows; j++)
            {
                for (int i = 0; i < Cols; i++)
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
            for (int j = 0; j < Rows; j++)
            {
                for (int i = 0; i < Cols; i++)
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
            for (int j = 0; j < Rows; j++)
            {
                for (int i = 0; i < Cols; i++)
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


#endif // ASENGINE_MATRIX_H