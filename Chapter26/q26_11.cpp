#include <iostream>
#include <vector>
#include <cstdlib>	// rand, srand
#include <ctime>	// time, clock
#include <stdexcept>
#include "Matrix.h"
using namespace std;
using namespace Numeric_lib;

int randint(int n){
	if(n <= 0) return 0;
	return rand() % n;
}

// m[n]の要素の合計
double row_sum(const Matrix<double, 2>& m, int n){
	double s = 0;
	for(int i = 0; i < m.dim2(); ++i) s += m[n][i];
	return s;
}

// m[0:n)の要素の合計
double row_accum(const Matrix<double, 2>& m, int n){
	double s = 0;
	for(int i = 0; i < n; ++i) s += row_sum(m, i);
	return s;
}

// ランダムな行列を作成
double rand_matrix(Matrix<double, 2>& m){
	for(int i = 0; i < m.dim1(); ++i){
		for(int j = 0; j < m.dim2(); ++j){
			m[i][j] = randint(20) - 10;
		}
	}
}

int main(){
	srand(time(NULL));

	int n;		// 次数
	cout << "input order: ";
	cin >> n;
	if(n <= 0) throw runtime_error("no positive order");

	Matrix<double, 2> m(n, n);	// n = 100000等の大きい数では、メモリが不足する可能性あり
	rand_matrix(m);

	char mode = 0;
	cout << "input mode(w: waste, b: better): ";
	cin >> mode;
	switch(mode){
		case 'w':	// 26.6の例（P.921）のアルゴリズム
		{
			vector<double> v;

			clock_t t1 = clock();
			if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");
			
			// mの行の合計を累計する
			for(int i = 0; i < m.dim1(); ++i) 
				v.push_back(row_accum(m, i + 1));
			
			clock_t t2 = clock();
			if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
			cout << "waste algorithm (order" << n << "): " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;

			break;
		}
		case 'b':	// より効率的なアルゴリズム
		{
			vector<double> v;

			clock_t t1 = clock();
			if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");

			double sum = 0;
			for(int i = 0; i < m.dim1(); ++i){
				sum += row_sum(m, i);
				v.push_back(sum);
			}

			clock_t t2 = clock();
			if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
			cout << "better algorithm (order" << n << "): " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;
		}
	}
}