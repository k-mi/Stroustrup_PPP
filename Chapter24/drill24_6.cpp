#include <iostream>
#include <iomanip>	// setw
#include "Matrix.h"
using namespace std;
using namespace Numeric_lib;

int main(){
	int n, m;		// 行数、列数
	cin >> n >> m;
	Matrix<int, 2> multiplication_matrix(n, m);

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			multiplication_matrix(i, j) = i * j;

	// 表示
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j)
			cout << setw(4) << multiplication_matrix(i, j);
		cout << endl;
	}
}