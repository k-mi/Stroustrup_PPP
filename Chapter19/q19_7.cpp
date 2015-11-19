#include <iostream>
#include <vector>
using namespace std;

template<class T> class Number{
public:
	explicit Number(T v = T()) : val(v) { }		// デフォルトコンストラクタ
	Number(const Number& n) : val(n.val) { }	// コピーコンストラクタ

	Number& operator=(const Number& n) { val = n.val; return *this; }	// コピー代入
	Number operator+(const Number& n) { return Number(val + n.val); }
	Number operator-(const Number& n) { return Number(val - n.val); }
	Number operator*(const Number& n) { return Number(val * n.val); }
	Number operator/(const Number& n) { return Number(val / n.val); }
	Number operator%(const Number& n) { return Number(val % n.val); }

	T val;	// データ
};

template<class T> istream& operator>>(istream& is, Number<T>& n){
	if(!is) return is;
	T tmp;
	cin >> tmp;
	if(!is) return is;
	n.val = tmp;
	return is;
}

template<class T> ostream& operator<<(ostream& os, const Number<T>& n){
	if(!os) return os;
	os << n.val;
	return os;
}

// すべてのvt[i].val*vu[i].valの合計を返す
template<class T, class U> double vector_multi(const vector<T>& vt, const vector<U>& vu){
	double add = 0;
	for(int i = 0; i < vt.size() && i < vu.size(); ++i)
		add += vt[i].val * vu[i].val;
	return add;
}

int main(){
	vector< Number<double> > vnd(20, Number<double>(0.01));
	vector< Number<int> > vni(20, Number<int>(314));

	cout << vector_multi(vnd, vni) << endl;
}