#ifndef ASENGINE_MATRIX_SERIALIAZATION_H
#define ASENGINE_MATRIX_SERIALIAZATION_H

#include "Matrix.h"
#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

#define ASENGINE_SERIALIAZE_MATRIX(MatrixType) \
template<> \
void Serializer<MatrixType>::Deserialize(const Json& object, MatrixType& dest) \
{ \
    ASENGINE_ASSERT(object.is_array(), "Matrix should be an array"); \
    ASENGINE_ASSERT(object.size() == MatrixType::GetColumnsSize(), "Invalid Columns size"); \
    \
    uint32_t j = 0; \
    for (const auto& col: object) \
    { \
        ASENGINE_ASSERT(col.is_array(), "Column should be an array"); \
        ASENGINE_ASSERT(col.size() == MatrixType::GetRowsSize(), "Invalid Rows Size"); \
        \
        uint32_t i = 0; \
        for (const auto& val: col) \
        { \
            dest[j][i] = val.get<float>(); \
            i++; \
        } \
        j++; \
    } \
} \
template<> \
Json Serializer<MatrixType>::Serialize(const MatrixType& src) \
{ \
    Json matrixObject = Json::array(); \
    for (uint32_t j = 0; j < MatrixType::GetColumnsSize(); j++) \
    { \
        Json column = Json::array(); \
        for (uint32_t i = 0; i < MatrixType::GetRowsSize(); i++) \
        { \
            column.push_back(src[j][i]); \
        } \
        matrixObject.push_back(column); \
    } \
    return matrixObject; \
}

#endif // ASENGINE_MATRIX_SERIALIAZATION_H