#include <iostream>

#include "matrix.h"

using namespace std;

int main() {
    NNumeric::TMatrix<int> m1(4, 4);

    for (auto& v : m1) {
        for (auto& e : v) e = 5;
    }

    for (const auto& v : m1.WithoutLines(2, 2)) {
        for (const auto& e : v) cout << e << " ";
        cout << "\n";
    }

    return 0;
}