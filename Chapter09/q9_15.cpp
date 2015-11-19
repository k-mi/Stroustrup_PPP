#include <iostream>
#include <stdexcept>
using namespace std;

const double usd_to_dkk = 6.62659784;	// USDからDKKへの換算

class Money{
public:
	enum Kind{
		USD, DKK
	};

	Money() : m_money(0), m_kind(USD) { } 
	Money(double d, Kind k) : m_money(d), m_kind(k) { }
	double money() const { return m_money; }
	Kind kind() const { return m_kind; }

private:
	double m_money;	// 金額
	Kind m_kind;	// 通貨の種類
};

ostream& operator<<(ostream& os, const Money& m){
	switch(m.kind()){
		case Money::USD:
			os << '$' << m.money();
			break;
		case Money::DKK:
			os << 'k' << m.money();
			break;			
	}	
	return os;
}

istream& operator>>(istream& is, Money& m){
	char c;
	double d;
	is >> c >> d;
	if(!is) return is;
	switch(c){
		case '$':
			m = Money(d, Money::USD);
			break;
		case 'k':
			m = Money(d, Money::DKK);
			break;
		default:
			is.clear(ios_base::failbit);
	}
	return is;
}

Money operator+(Money& a, Money& b){
	if(a.kind() == b.kind())
		return Money(a.money() + b.money(), a.kind());
	else if(a.kind() == Money::USD)
		return Money(a.money() + b.money() / usd_to_dkk, a.kind());
	else if(a.kind() == Money::DKK)
		return Money(a.money() + b.money() * usd_to_dkk, a.kind());
}

Money operator-(Money& a, Money& b){
	if(a.kind() == b.kind())
		return Money(a.money() - b.money(), a.kind());
	else if(a.kind() == Money::USD)
		return Money(a.money() - b.money() / usd_to_dkk, a.kind());
	else if(a.kind() == Money::DKK)
		return Money(a.money() - b.money() * usd_to_dkk, a.kind());
}

int main(){
	Money m1, m2;
	cin >> m1 >> m2;

	cout << m1 << endl;
	cout << m2 << endl;
	cout << m1 + m2 << endl;
	cout << m1 - m2 << endl;
}