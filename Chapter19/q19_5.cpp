#include <iostream>
using namespace std;

class Int{
public:	
	Int() : val(0) { }					// デフォルトコンストラクタ
	Int(int v) : val(v) { }				// コンストラクタ（暗黙の型変換を許可）
	Int(const Int& i) : val(i.val) { }	// コピーコンストラクタ

	Int& operator=(const Int& i) { val = i.val; return *this; }	// コピー代入
	Int operator+(const Int& i) { return Int(val + i.val); }
	Int operator-(const Int& i) { return Int(val - i.val); }
	Int operator*(const Int& i) { return Int(val * i.val); }
	Int operator/(const Int& i) { return Int(val / i.val); }

	int val;	// 値
};

istream& operator>>(istream& is, Int& i){
	if(!is) return is;
	int tmp;
	cin >> tmp;
	if(!is) return is;
	i.val = tmp;
	return is;
}

ostream& operator<<(ostream& os, const Int& i){
	if(!os) return os;
	os << i.val;
	return os;
}

int main(){
	Int a(3131), b = 2828, c;
	cout << a << ' ' << b << ' ' << c << endl;

	cin >> a >> b >> c;
	cout << a << ' ' << b << ' ' << c << endl;

	a = a * b * c;
	cout << a << ' ' << b << ' ' << c << endl;

	a = b = c = 0;
	cout << a << ' ' << b << ' ' << c << endl;
}