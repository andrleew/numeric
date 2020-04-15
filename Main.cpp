#include <iostream>
#include <vector>

#include "LU.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    NNumeric::Matrix A;
    NNumeric::Vector b;
    NNumeric::ReadMatrix(A, n);
    NNumeric::ReadVector(b, n);
    cout << "res:\n" << NNumeric::LU(A, b) << "\n";
    cout << "determinant:\n" << NNumeric::Determinant(A) << "\n\n";
    cout << "inverse:\n" << NNumeric::Inverse(A) << "\n";
    return 0;
}