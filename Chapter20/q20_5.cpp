#include <iostream>
#include <vector>
using namespace std;

template<class T> istream& operator>>(istream& is, vector<T>& v){
	if(!is) return is;
	T tmp;
	is >> tmp;
	if(!is) return is;
	v.push_back(tmp);
	return is;
}

template<class T> ostream& operator<<(ostream& os, const vector<T>& v){
	if(!os) return os;
	for(int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	return os;
}

int main(){
	vector<double> vd(10, 31.9);
	vd[4] = 25.2;
	vd[9] = 3.14;

	cout << vd << endl;

	cin >> vd >> vd;		// 末尾に2つ要素を追加
	cout << vd << endl;
}