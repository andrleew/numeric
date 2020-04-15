#include "LU.h"

void NNumeric::LU(const Matrix& A, Matrix& L, Matrix& U) {
    Resize(L, A.size());
    U=A;

	for(size_t i = 0; i < A.size(); i++)
		for(size_t j = i; j < A.size(); j++)
			L[j][i]=U[j][i]/U[i][i];
	
	for(size_t k = 1; k < A.size(); k++)
	{
		for(size_t i = k-1; i < A.size(); i++)
			for(size_t j = i; j < A.size(); j++)
				L[j][i] = U[j][i]/U[i][i];

		for(size_t i = k; i < A.size(); i++)
			for(size_t j = k-1; j < A.size(); j++)
				U[i][j] -= L[i][k-1]*U[k-1][j];
	}
}

NNumeric::Vector NNumeric::LU(const Matrix& A, const Vector& b) {
	Matrix L, U;
	LU(A, L, U);
	return Gauss(U, Gauss(L, b, EGaussType::LU_L), EGaussType::LU_U);
}