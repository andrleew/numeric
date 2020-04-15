#include "Vector.h"

void NNumeric::ReadVector(Vector& v, size_t n) {
    Resize(v, n);
    for (auto& el : v)
        std::cin >> el;
}

std::ostream& operator<< (std::ostream& os, const NNumeric::Vector& v) {
    for (const auto& el : v) {
        os << el << " ";
    }
    os << "\n";
    return os;
}