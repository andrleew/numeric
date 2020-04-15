#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>

namespace NNumeric {
    using Vector = std::vector<double>;
    
    void ReadVector (Vector&, size_t size);
    inline void Resize(Vector& v, size_t size) {
        v.resize (size);
    }

} // namespace NNumeric

std::ostream& operator<<(std::ostream&, const NNumeric::Vector&);

#endif