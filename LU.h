#ifndef LU_H
#define LU_H

#include "Matrix.h"

#include <iostream>
#include <vector>

namespace NNumeric {
    void LU(const Matrix& A, Matrix& L, Matrix& U);
    Vector LU(const Matrix&, const Vector&);
} // namespace NMatrixFunctions

#endif