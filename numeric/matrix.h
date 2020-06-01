#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <iostream>
#include <algorithm>

namespace NNumeric {
    template<class T>
    class TMatrix {
    public:
        TMatrix(const TVector<T>& vec)
        : Matrix(1, vec){}

        TMatrix(size_t size1 = 10, size_t size2 = 10) {
            Matrix.Resize(size1, TVector<T>(size2));
        }

        TMatrix(const TMatrix<T>& m)
        : Matrix(m.Matrix)
        {}

        inline size_t RowsCount() const {
            return Matrix.Size();
        }

        inline size_t ColumnsCount() const {
            return Matrix[0].Size();
        }

        inline void Resize(size_t rowCount, size_t columnCount) {
            Matrix.Resize(rowCount, TVector<T>(columnCount));
        }

        const TVector<TVector<T>>& GetRef() const {
            return Matrix;
        }

        TVector<TVector<T>>& GetRef() {
            return Matrix;
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
        
        template <typename OP>
        inline void ForEach(OP func) {
            Matrix.ForEach([&](TVector<T>& v) {v.ForEach(func);});
        }

        template <typename OP>
        inline void ForEach(const OP& func) const {
            Matrix.ForEach([&func](const auto& v) {v.ForEach(func);});
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
        
        static TMatrix<T> MakeMatrix(const TVector<T>& v) {
            TMatrix<T> res (v.Size(), 1);
            for (size_t i = 0; i < v.Size(); ++i) res[i][0] = v[i];
            return res;
        }

        static TVector<T> MakeVector(const TMatrix<T>& m) {
            size_t size = 0;
            for (const auto& el : m) size += el.Size();
            TVector<double> v(size);
            size_t i = 0;
            m.ForEach([&v, &i] (const auto& el) {v[i++] = el;});
            return v;
        }

        void ReadMatrix(std::istream& is) {
            ForEach([&is](T& t) {is >> t;} );
        }

        static void ReadMatrix(TMatrix<T>& m) {
            m.ReadMatrix();
        }

        void WriteMatrix() const {
            for (const auto& v : Matrix) {
                for (const auto& t : v) std::cout << t << " ";
                std::cout << "\n";
            }
        }

        static void WriteMatrix(const TMatrix<T>& m) {
            m.WriteMatrix();
        }

    public:

        TMatrix<T>& Transpose() {
            for (size_t i = 0; i < RowsCount(); ++i)
                for (size_t j = 0; j < i; ++j)
                    std::swap(Matrix[i][j], Matrix[j][i]);
            return *this;
        }

        TMatrix<T> GetTransposed() const {
            TMatrix<T> matr (*this);
            matr.Transpose();
            return matr;
        }

        TMatrix<T>& Mult(const T& value) {
            ForEach([&value](T& t) { t *= value;});
            return *this;
        }

        TMatrix<T> Summ(const TMatrix<T>& matr) const {
            TMatrix<T> result(RowsCount(), matr.ColumnsCount());
            for (size_t i = 0; i < RowsCount(); ++i) {
                for (size_t j = 0; j < ColumnsCount(); ++i) {
                    result = Matrix[i][j] + matr[i][j];
                }
            }
            return result;
        }

        TVector<T> Mult(const TVector<T>& vec) const {
            TVector<T> res(RowsCount(), 0);
            for (size_t i = 0; i < RowsCount(); ++i) {
                for (size_t j = 0; j < ColumnsCount(); ++j) {
                    res[i] += Matrix[i][j] * vec[j];
                }
            }
            return res;
        }

        TMatrix<T> Mult(const TMatrix<T>& matr) const {
            TMatrix<T> result(RowsCount(), matr.ColumnsCount());
            for (size_t i = 0; i < matr.RowsCount(); ++i) {
                for (size_t j = 0; j < matr.ColumnsCount(); ++j) {
                    for (size_t k = 0; k < RowsCount(); ++k) {
                        result[i][j] += Matrix[i][k] * matr[k][j];
                    }
                }
            }
            return result;
        }

        TMatrix<T> WithoutLines(size_t row, size_t col) const {
            TMatrix<T> res(RowsCount() - 1, ColumnsCount() - 1);
            for (size_t i = 0, r = 0; i < RowsCount(); ++i, ++r) {
                if (i == row) --r;
                else {
                    for (size_t j = 0, c = 0; j < ColumnsCount(); ++j, ++c) {
                        if (j != col) res[r][c] = Matrix[i][j];
                        else --c;
                    }
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
                T sum = 0;
                double pow = 1;
                for (size_t i = 0; i < RowsCount(); ++i) {
                    sum += pow * Minor(0, i) * Matrix[0][i];
                    pow *= -1;
                }
                return sum;
            }
        }

        TMatrix<T> GetInversed() const {
            TMatrix<T> res(RowsCount(), ColumnsCount());
            for (size_t i = 0; i < RowsCount(); ++i)
                for (size_t j = 0; j < ColumnsCount(); ++j)
                    res[i][j] = Minor(i, j) * ((i + j) % 2 ? -1 : 1);
            return res.Transpose().Mult(1 / Determinant());
        }

        TMatrix<T> Inverse() {
            *this = GetInversed();
        }

        T GetNorm() {
            T Max = std::numeric_limits<T>::min();
            Matrix.ForEach([&Max](const auto& el) {
                Max = max(Max, el.Norm());
            });
            return Max;
        }

    private:

        TVector<TVector<T>> Matrix;
    };
}

#endif // MATRIX_H