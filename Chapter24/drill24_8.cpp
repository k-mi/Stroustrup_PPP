#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"
using namespace std;
using namespace Numeric_lib;

int main(){
	Matrix<int, 2> m(2, 3);
	cin >> m;

	cout << m << endl;
}