#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Money{
public:
	Money() : m_cent(0) { } 
	Money(long int i) : m_cent(i) { }
	long int cent() const { return m_cent; }

private:
	long int m_cent;	// セント
};

ostream& operator<<(ostream& os, const Money& m){
	os << '$' << m.cent() / 100.0 << endl;
	return os;
}

istream& operator>>(istream& is, Money& m){
	char c;
	double d;
	is >> c >> d;
	if(!is) return is;
	if(c != '$'){
		is.clear(ios_base::failbit);
		return is;
	}
	m = Money(int(round(d * 100)));

	return is;
}

int main(){
	Money money;

	cin >> money;
	cout << money;
}