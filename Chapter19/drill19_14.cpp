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

// 14
template<class T> istream& operator>>(istream& is, vector<T>& v){
	if(!is) return is;

	char ch1, ch2, ch3, ch4;
	T val1, val2, val3;
	cin >> ch1 >> val1 >> ch2 >> val2 >> ch3 >> val3 >> ch4;
	if(!is || ch1 != '{' || ch2 != ',' || ch3 != ',' || ch4 != '}') return is;

	v.push_back(val1);
	v.push_back(val2);
	v.push_back(val3);

	return is;
}

// 14
template<class T> ostream& operator<<(ostream& os, const vector<T>& v){
	if(!os) return os;

	if(v.size() >= 3)
		os << "{ " << v[0] << ", " << v[1] << ", " << v[2] << " }";
	return os;
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
	S< vector<int> > sv(vector<int>(3));

	cout << si.get() << endl;
	cout << sc.get() << endl;
	cout << sd.get() << endl;
	cout << ss.get() << endl;
	cout << sv.get() << endl;

	read_val(si);
	cout << si.get() << endl;
	read_val(sc);
	cout << sc.get() << endl;
	read_val(sd);
	cout << sd.get() << endl;
	read_val(ss);
	cout << ss.get() << endl;
	read_val(sv);
	cout << sv.get() << endl;
}