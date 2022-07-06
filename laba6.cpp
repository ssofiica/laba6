#include "Polynomial.h"

int main()
{
	Polynomial P, D;
	Polynomial Mult;
	Polynomial Sum;
	cin >> P;
	cin >> D;
	cout << "P: " << P << '\n';
	cout << "D: " << D << '\n';
	Sum = D + P;
	Mult = D * P;
	Polynomial DCopy = D;
	D += P;
	cout << "Sum: " << Sum << '\n';
	cout << "+=   " << D << '\n';
	DCopy *= P;
	cout << "D*P: " << Mult << '\n';
	cout << "*=   "<< DCopy << '\n';
	return 0;
}
