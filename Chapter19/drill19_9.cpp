#include <iostream>
#include <vector>
using namespace std;

template<class T> class S {
public:
	explicit S(T v) : val(v) { }	// コンストラクタ
	
	T& get();
	void set(const T& v);

private:
	T val; 							// 値
};

// valを取得する
template<class T> T& S<T>::get(){
	return val;
}

// valを変更する
template<class T> void S<T>::set(const T& v) {
	val = v;
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
	cout << sv.get()[9] << endl;

	si.set(1234);
	sc.set('B');
	sd.set(1.41421356);
	ss.set("Banana");
	sv.set(vector<int>(20, 3131));

	cout << si.get() << endl;
	cout << sc.get() << endl;
	cout << sd.get() << endl;
	cout << ss.get() << endl;
	cout << sv.get()[19] << endl;
}