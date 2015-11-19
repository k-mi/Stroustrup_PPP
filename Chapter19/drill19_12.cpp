#include <iostream>
#include <vector>
using namespace std;

template<class T> class S {
public:
	explicit S(T v) : val(v) { }	// コンストラクタ

	T& operator=(const T& v);
 
	T& get();
	const T& get() const;

private:
	T val; 							// 値
};

// valを変更する
template<class T> T& S<T>::operator=(const T& v) {
	val = v;
	return val;
}

// valを取得する
template<class T> T& S<T>::get(){
	return val;
}

template<class T> const T& S<T>::get() const{
	return val;
}

// 13
template<class T> istream& operator>>(istream& is, S<T>& s){
	if(!is) return is;

	T tmp;
	is >> tmp;
	s = tmp;
	return is;
}

// 13
template<class T> ostream& operator<<(ostream& os, const S<T>& s){
	if(!os) return os;

	os << s.get();
	return os;
}

// 12
// cinからvに読み込む
template<class T> void read_val(T& v){	
	while(true){
		cin >> v;

		if(cin){
			break;
		}
		else{
			cin.clear();
			cin.ignore();
		}
	}
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

	read_val(si);
	cout << si.get() << endl;
	read_val(sc);
	cout << sc.get() << endl;
	read_val(sd);
	cout << sd.get() << endl;
	read_val(ss);
	cout << ss.get() << endl;
}