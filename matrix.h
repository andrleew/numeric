#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

namespace NNumeric {

    template<typename T>
    class TMatrix {
    public:
        TMatrix(const TVector<T>& vec)
        : Matrix(1, vec){}

        TMatrix(size_t size1 = 10, size_t size2 = 10) {
            Matrix.Resize(size1, TVector<T>(size2));
        }

        inline size_t RowsCount() const {
            return Matrix.Size();
        }

        inline size_t ColumnsCount() const {
            return Matrix[0].Size();
        }

        const TVector<TVector<T>>& GetRef() const {
            return Matrix;
        }

        TVector<TVector<T>>& GetRef() {
            return const_cast<TVector<TVector<T>>&>(GetRef());
        }

        inline decltype(auto) begin() {
            return Matrix.begin();
        }

        inline decltype(auto) end() {
            return Matrix.end();
        }

        inline decltype(auto) begin() const {
            return Matrix.begin();
        }

        inline decltype(auto) end() const {
            return Matrix.end();
        }
        const TVector<T>& operator[](size_t id) const {
            return Matrix[id];
        }

        TVector<T>& operator[](size_t id) {
            return const_cast<TVector<T>&>(Matrix[id]);
        }

        TMatrix<T>& operator=(const TMatrix<T>& rhs) {
            Matrix = rhs.Matrix;
            return *this;
        }

    public:

        void Transpose() {
            for (size_t i = 0; i < RowsCount(); ++i)
                for (size_t j = 0; j < i; ++j)
                    std::swap(Matrix[i][j], Matrix[j][i]);
            return *this;
        }

        TMatrix Transpose() const {
            TMatrix matr(Matrix);
            matr.Transpose();
            return matr;
        }

        void Mult(const T& value) {
            Matrix.ForEach([&value](TVector<T>& vec) {
                vec.ForEach([&value](T& v) {
                    v *= value;
                });
            });
        }

        TMatrix Mult(const TMatrix<T> matr) {
            TMatrix result(RowsCount(), matr.ColumnsCount());
            for (size_t i = 0; i < matr.ColumnsCount(); ++i) {
                for (size_t j = 0; j < ColumnsCount(); ++j) {
                    for (size_t k = 0; k < RowsCount(); ++k) {
                        result[i][j] += Matrix[i][k] * matr[k][j];
                    }
                }
            }
            return result;
        }

        TMatrix WithoutLines(size_t row, size_t col) const {
            TMatrix res(RowsCount() - 1, ColumnsCount() - 1);
            for (size_t i = 0, r = 0; i < RowsCount(); ++i, r += (i != row)) {
                for (size_t j = 0, c = 0; j < ColumnsCount(); ++j, c += (j != col)) {
                    res[r][c] = Matrix[i][j];
                }
            }
            return res;
        }

        inline T Minor(size_t row, size_t col) const {
            return WithoutLines(row, col).Determinant();
        }

        T Determinant() const {
            if (RowsCount() < 1) return 0;
            else if (RowsCount() == 1) return Matrix[0][0];
            else if (RowsCount() == 2) 
                return Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0];
            else {
                T sum, pow = 1;
                for (size_t i = 0; i < RowsCount(); ++i) {
                    sum += pow * Minor(0, i) * Matrix[0][i];
                    pow *= -1;
                }
            }
        }

    private:
        TVector<TVector<T>> Matrix;
    };
}
#endif // MATRIX_H