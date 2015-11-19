#include <iostream>
#include <complex>
#include "Matrix.h"
using namespace std;
using namespace Numeric_lib;

int main(){
	Matrix< complex<double> > matrix_cd(10);

	for(int i = 0; i < matrix_cd.size(); ++i)
		cin >> matrix_cd[i];	// supported formats: re, (re), (re,im)

	complex<double> sum = 0;
	for(int i = 0; i < matrix_cd.size(); ++i)
		sum += matrix_cd[i];
	
	cout << sum << endl;
}