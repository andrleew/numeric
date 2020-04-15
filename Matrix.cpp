#include "Matrix.h"

#include <algorithm>

std::ostream& operator<<(std::ostream& os, const NNumeric::Matrix& m) {
    for (const auto& v: m) {
        for (const auto& el : v) {
            os << el << " ";
        }
        os << "\n";
    }
    return os;
}

void NNumeric::ReadMatrix(Matrix& matr, uint64_t size) {
    Resize(matr, size);
    for (auto& vec : matr) {
        for (auto& element: vec) {
            std::cin >> element;
        }
    }
}

void NNumeric::Mult(const Matrix& m1, const Matrix& m2, Matrix& result) {
    Resize(result, m1.size(), m2.size());
    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m2.size(); ++j) {
            for (size_t k = 0; k < m2.size(); ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void NNumeric::Mult(const Matrix& m, double value, Matrix& result) {
    Resize(result, m.size(), m[0].size());
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m[i].size(); ++i) {
            result[i][j] = m[i][j] * value;
        }
    }
}

NNumeric::Matrix& NNumeric::Mult(Matrix& m, double value) {
    for (auto& vec : m)
        for (auto& el : vec)
            el *= value;
    return m;
}

NNumeric::Matrix& NNumeric::Mult(const Matrix& m1, const Matrix& m2) {
    static Matrix result;
    Mult(m1, m2, result);
    return result;
}

void NNumeric::SummMatrix(const Matrix& m1, const Matrix& m2, Matrix& result) {
    for (size_t i = 0; i < m1.size(); ++i) {
        for (size_t j = 0; j < m2.size(); ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

NNumeric::Matrix& NNumeric::SummMatrix(const Matrix& m1, const Matrix& m2) {
    static Matrix result;
    SummMatrix(m1, m2, result);
    return result;
}

NNumeric::Vector Gauss_L(const NNumeric::Matrix& matr, const NNumeric::Vector& b) {
    NNumeric::Vector result = b;    
    
    for (size_t i = 0; i < matr.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            result[i] -= matr[i][j] * result[j];
        }
    }

    return result;
}

NNumeric::Vector Gauss_U(const NNumeric::Matrix& matr, const NNumeric::Vector& b) {
    NNumeric::Vector result = b;

    for (int i = matr.size() - 1; i >= 0; --i) {
        for (int j = matr.size() - 1; j >= i; --j) {
            result[i] -= matr[i][j] * result[j] / matr[j][j];
        }
    }

    return result;
}

NNumeric::Vector NNumeric::Gauss(const Matrix& matr, const Vector& b, EGaussType type) {
    switch (type) {
    case EGaussType::LU_L:
        return Gauss_L(matr, b);
    case EGaussType::LU_U:
        return Gauss_U(matr, b);
    default:
        return Vector();
    }
}

NNumeric::Matrix MatrixWithout(const NNumeric::Matrix& matr, size_t idRow, size_t idCol) {
    NNumeric::Matrix m (matr.size() - 1, NNumeric::Vector(matr[0].size() - 1));
    for (size_t mi = 0, i = 0; i < matr.size(); ++i, ++mi) {
        if (i == idRow) {
            --mi;
        } else {
            for (size_t j = 0, mj = 0; j < matr[i].size(); ++j, ++mj) {
                if (j == idCol) {
                    --mj;
                } else {
                    m[mi][mj] = matr[i][j];
                }
            }
        }
    }
    return m;
}

double NNumeric::Determinant(const Matrix& matr) {
    if (matr.size() < 1) return 0;
    else if (matr.size() == 1) return matr[0][0];
    else if (matr.size() == 2)
        return matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0];
    else {
        double sum = 0, pow = 1;
        for (size_t i = 0; i < matr.size(); ++i) {
            sum += pow * Minor(matr, 0, i) * matr[0][i];
            pow *= -1;
        }
        return sum;
    }
}

double NNumeric::Minor(const Matrix& matr, size_t i, size_t j) {
    return Determinant(MatrixWithout(matr, i, j));
}

NNumeric::Matrix NNumeric::Transpose(const Matrix& matr) {
    Matrix m(matr[0].size(), Vector(matr.size()));
    for (size_t i = 0; i < matr.size(); ++i) {
        for (size_t j = 0; j < matr[0].size(); ++j) {
            m[j][i] = matr[i][j];
        }
    }
    return m;
}

NNumeric::Matrix NNumeric::Inverse(const NNumeric::Matrix& matr) {
    double det = Determinant(matr);
    Matrix m (matr[0].size(), Vector(matr.size()));
    for (size_t i = 0; i < matr.size(); ++i) {
        for (size_t j = 0; j < matr[i].size(); ++j) {
            m[i][j] = Minor(matr, i, j);
            if ((i + j) % 2) {
                m[i][j] *= -1;
            }
        }
    }
    auto transposed = Transpose(m);
    std::cout << transposed << "\n";
    return Mult(transposed, 1 / det);
}