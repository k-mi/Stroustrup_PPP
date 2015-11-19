#include <iostream>
#include <vector>
using namespace std;

template<class T> class S {
public:
	explicit S(T v) : val(v) { }	// コンストラクタ
	T& get();

private:
	T val; 							// 値
};

template<class T> T& S<T>::get(){
	return val;
}

int main(){
	S<int> si(3131);
	S<char> sc('A');
	S<double> sd(3.141592);
	S<string> ss("Apple");
	S< vector<int> > sv(vector<int>(10, 2828));

	cout << si.get() << endl;
	cout << sc.get() << endl;
	cout << sd.get() << endl;
	cout << ss.get() << endl;
	cout << sv.get()[0] << endl;
}