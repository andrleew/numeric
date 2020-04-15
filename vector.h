#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <functional>
#include <algorithm>

namespace NNumeric {

    template<typename T>
    class TVector {
    public:
        TVector() {}

        TVector(const size_t size) {
            Array.resize(size);
        }

        TVector(const size_t size, const T& value)
        : Array(size, value)
        {}

        TVector(const std::vector<T>& array)
        : Array(array)
        {
        }

        inline size_t Size() const {
            return Array.size();
        }

        inline void Resize(const size_t size) {
            Array.resize(size);
        }

        inline void Resize(const size_t size, const T& value) {
            Array.resize(size, value);
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

        inline void ForEach(const std::function<void(const T&)>& func) const {
            std::for_each(Array.begin(), Array.end(). func);
        }

        inline void ForEach(const std::function<void(T&)>& func) {
            std::for_each(Array.begin(), Array.end(), func);
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

        inline operator std::vector<T>() {
            return Array;
        }

        TVector& operator=(const TVector& rhs) {
            Array = rhs.Array;
            return *this;
        }

    private:
        std::vector<T> Array;
    };

}

#endif // !VECTOR_H