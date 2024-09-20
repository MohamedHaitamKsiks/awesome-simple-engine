#ifndef __ASENGINE_SQUARE_MATRIX_H
#define __ASENGINE_SQUARE_MATRIX_H

#include <cstdint>
#include "Matrix.h"



namespace ASEngine
{
    template <size_t N, size_t Stride>
    class  SquareMatrix : public Matrix<N, N, Stride>
    {
    public:
        constexpr SquareMatrix(): Matrix<N, N, Stride>()
        {
        }

        constexpr SquareMatrix(const Matrix<N, N, Stride>& matrix): Matrix<N, N, Stride>(matrix)
        {
        }

        // calculate transpose
        constexpr SquareMatrix Transpose() const
        {
            SquareMatrix result;
            for (int j = 0; j < N; j++)
            {
                for (int i = 0; i < N; i++)
                {
                    result[i][j] = (*this)[j][i];
                }
            }

            return result;
        }
        
        // trace of matrix
        constexpr float Trace() const
        {
            float trace = 0.0f;
            
            for (int i = 0; i < static_cast<int>(N); i++)
            {
                trace += (*this)[i][i];
            }

            return trace;
        }

        // create matrix from diags
        static constexpr SquareMatrix Diagonal(float d)
        {
            SquareMatrix result;
            for (int j = 0; j < static_cast<int>(N); j++)
            {
                for (int i = 0; i < static_cast<int>(N); i++)
                {
                    if (i == j)
                        result[i][j] = d;
                    else
                        result[i][j] = 0.0f;
                }
            }

            return result;
        }

        // define constants
        // identity matrix
        static inline constexpr SquareMatrix IDENTITY() 
        {
            return Diagonal(1.0f);
        }
        
        // zero matrix
        static inline constexpr SquareMatrix ZERO() 
        {
            return Diagonal(0.0f);
        }

    };
} // namespace ASEngine


#endif // __ASENGINE_SQUARE_MATRIX_H