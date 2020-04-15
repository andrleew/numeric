#include <iostream>
#include <vector>

using namespace std;

void LU(vector <vector <double>> A, vector <vector <double>> &L, 
		vector <vector <double>> &U, int n)
{
	U=A;

	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++)
			L[j][i]=U[j][i]/U[i][i];
	
	for(int k = 1; k < n; k++)
	{
		for(int i = k-1; i < n; i++)
			for(int j = i; j < n; j++)
				L[j][i]=U[j][i]/U[i][i];

		for(int i = k; i < n; i++)
			for(int j = k-1; j < n; j++)
				U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j];
	}

}

void proisv(vector <vector <double>> A, vector <vector <double>> B, 
			vector <vector <double>> &R, int n)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				R[i][j] += A[i][k] * B[k][j];
}

void show(vector <vector <double>> A, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout <<"\t"<< A[i][j] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	const int n=4;
	vector <vector <double>> A (n), L (n), U(n), R(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			A[i].push_back(rand()%20-10);
			L[i].push_back(0);
			U[i].push_back(0);
			R[i].push_back(0);
		}
	}
	LU(A,L,U,n);
	cout << "Fisrt matrix" << endl;
	show(A,n);
	cout << "U matrix" << endl;
	show(U,n);
	cout << "L matrix" << endl;
	show(L,n);
	proisv(L,U,R,n);
	cout << "L*U matrix" << endl;
	show(R,n);
	return 0;
}