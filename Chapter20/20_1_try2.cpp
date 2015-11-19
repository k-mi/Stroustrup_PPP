#include <iostream>
#include <vector>
using namespace std;

// 最も大きな値を持つ[first,last)の範囲内の要素へのポインタを返す
double* high(double* first, double* last){
	// 最大値が-1未満の場合、
	// 初期化されていないポインタが返される
	// double h = -1;
	// double* high;
	double h = *first;		// 最初の要素とそのポインタで初期化する
	double* high = first;
	for(double* p = first + 1; p < last; ++p)	// 次の要素から比較を開始
		if(h < *p) { high = p; h = *p; }		
	return high;
}

int main(){
	double array[5] = {-10.9, -1, -2, -0.008, -6.28};

	cout << *high(array, &array[5]) << endl;
}