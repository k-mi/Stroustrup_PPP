#include <iostream>
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

int main(){
	Number<double> a(31.31), b = Number<double>(28.28), c;
	cout << a << ' ' << b << ' ' << c << endl;
	cin >> a >> b >> c;
	cout << a << ' ' << b << ' ' << c << endl;
	a = a * b * c;
	cout << a << ' ' << b << ' ' << c << endl;

	Number<int> d(31), e(29);
	//cout << a % b << endl;	// error: invalid operands to binary expression
	cout << d % e << endl;
}