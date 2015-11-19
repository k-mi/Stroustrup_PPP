#include <iostream>
#include <vector>
using namespace std;

template<class T> struct S {
	explicit S(T v) : val(v) { }	// コンストラクタ

	T val; 							// 値
};

int main(){
	S<int> si(3131);
	S<char> sc('A');
	S<double> sd(3.141592);
	S<string> ss("Apple");
	S < vector<int> >(vector<int>(10, 2828));
}