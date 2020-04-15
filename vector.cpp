#include "vector.h"

#include <iostream>

using namespace std;

int main() {
    NNumeric::TVector<double> v(10);
    for (auto& el : v) el = 5;
    for (const auto& el : v) cout << el << " ";
    return 0;
}