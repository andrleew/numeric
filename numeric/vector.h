#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <functional>
#include <algorithm>
#include <execution>
#include <cmath>
#include <cassert>
#include <iostream>

namespace NNumeric {

    template<typename T>
    class TVector {
    public:
        TVector() {}

        TVector(const size_t size) 
        : Array(size, 0) {}

        TVector(const size_t size, const T& value)
        : Array(size, value)
        {}

        TVector(const TVector<T>& v)
        : Array(v.Array)
        {}

        TVector(const std::vector<T>& array)
        : Array(array)
        {}

        inline size_t Size() const {
            return Array.size();
        }

        inline void Resize(const size_t size) {
            Array.resize(size);
        }

        inline void Resize(const size_t size, const T& value) {
            Resize(size);
            ForEach([&value](auto& el) {el = value;});
        }

        inline bool IsEmpty() const {
            return Array.empty();
        }

        inline const std::vector<T>& GetRef() const {
            return Array;
        }

        inline std::vector<T>& GetRef() {
            return const_cast<std::vector<T>&>(GetRef());
        }

        template <typename OP>
        inline void ForEach(OP func) {
            for (auto& el : Array) func(el);
        }

        template <typename OP>
        inline void ForEach(const OP& func) const {
            std::for_each(std::execution::par_unseq, begin(), end(), func);
        }

        inline T Norm() const {
            T norm = 0;
            ForEach([&norm] (const auto& el) {norm += abs(el);});
            return norm;
        }

        inline T Sum() const {
            T sum = 0;
            ForEach([&sum](const auto& el) {sum += el;});
            return sum;
        }

        inline T AvgSqr() const {
            T sum = 0;
            ForEach([&sum](const auto& el) {sum += el * el;});
            return std::sqrt(sum);
        }

        inline void Mult(const T& value) {
            ForEach([&value](auto& el) {el *= value;});
        }

        TVector<T> GetMulted(const T& value) {
            TVector<T> v (*this);
            v.Mult(value);
            return v;
        }

        T Mult(const TVector<T>& vec) {
            if (Array.size() != vec.Size()) return T();
            T t = 0;
            for (size_t i = 0; i < Size(); ++i)
                t += Array[i] * vec[i];
            return t;
        }

        TVector<T> Minus(const TVector<T>& v) const {
            assert(Size() == v.Size());
            TVector<T> result(Array.size());
            result.Minus(v);
            return result;
        }

        void Minus(const TVector<T>& v) {
            assert (v.Size() == Size());
            for (size_t i = 0; i < Array.size(); ++i) {
                Array[i] -= v[i];
            }
        }

        void Sum(const TVector<T>& vec) {
            size_t i = 0;
            ForEach([&vec, &i](auto& el) {el += vec[i++];});
        }

        inline size_t FindNot(const T& value, size_t begin = 0) {
            while (begin < Array.size()){
                if (Array[begin] == value) return begin;
                else ++begin;
            }
            return begin;
        }

        inline decltype(auto) begin() {
            return Array.begin();
        }

        inline decltype(auto) end() {
            return Array.end();
        }

        inline decltype(auto) begin() const {
            return Array.begin();
        }

        inline decltype(auto) end() const {
            return Array.end();
        }

        inline T& operator[](const size_t id) {
            return const_cast<T&>(Array[id]);
        }

        inline const T& operator[](const size_t id) const {
            return Array[id];
        }

        inline T Get(size_t i) const {
            return i < Size() ? Array[i] : 0;
        }

        inline operator std::vector<T>() {
            return Array;
        }

        TVector<T>& operator=(const TVector<T>& rhs) {
            this->Array = rhs.Array;
            return *this;
        }

    private:
        std::vector<T> Array;
    };

}

#endif // !VECTOR_H