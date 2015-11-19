#include <iostream>
#include <vector>
#include <algorithm>	// sort
#include <cstdlib>		// rand, srand
#include <ctime>		// time, clock
using namespace std;

// [0:1)の浮動小数点数の乱数を生成
double frand(){
	return double(rand()) / RAND_MAX;
}

int main(){
	srand(time(NULL));
	clock_t t1, t2;

	// 500,000
	vector<double> v1;
	t1 = clock();
	if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");
	
	for(int i = 0; i < 500000; ++i)
		v1.push_back(frand());
	sort(v1.begin(), v1.end());

	t2 = clock();
	if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
	cout << "500,000 double sort: " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;

	// 5,000,000
	vector<double> v2;
	t1 = clock();
	if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");

	for(int i = 0; i < 5000000; ++i)
		v2.push_back(frand());
	sort(v2.begin(), v2.end());

	t2 = clock();
	if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
	cout << "5,000,000 double sort: " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;
}