#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

#include "Vector.h"

namespace NNumeric {
    using Matrix = std::vector<Vector>;

    enum EGaussType {
        None,
        LU_L,
        LU_U
    };

    inline void Resize(Matrix& m, size_t size1, size_t size2 = 0) {
        size2 = size2 ? size2 : size1;
        m.resize(size1, Vector(size2));
    }

    void ReadMatrix(Matrix&, uint64_t size = 3);
    void Mult(const Matrix& m1, const Matrix& m2, Matrix& result);
    void Mult(const Matrix& m, double value, Matrix& result);
    Matrix& Mult(Matrix& m, double value);
    Matrix& Mult(const Matrix& m1, const Matrix& m2);
    void SummMatrix(const Matrix&, const Matrix&, Matrix&);
    Matrix& SummMatrix(const Matrix&, const Matrix&);
    double Minor(const Matrix&, size_t i, size_t j);
    double Determinant(const Matrix&);
    Matrix Transpose(const Matrix&);
    Matrix Inverse(const Matrix&);

    Vector Gauss(const Matrix&, const Vector &, const EGaussType = EGaussType::None);
    void Normalize(Matrix&);

    inline Matrix ToMatrix(const Vector& v) {
        return Matrix(1, v);
    }
    Vector ToVector(const Matrix& m) {
        Vector v;
        for (const auto& el : m[0])
            v.push_back(el);
        return v;
    }
} // namespace Matrix


std::ostream& operator<<(std::ostream& os, const NNumeric::Matrix& m);

#endif