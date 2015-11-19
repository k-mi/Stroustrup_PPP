#include <iostream>
#include <stdexcept>
using namespace std;

class Rational{
public:
	Rational(int d, int n);

	int denominator() const { return m_denominator; }
	int numerator() const { return m_numerator; }
	operator double() const;

private:
	int m_denominator;	// 分母
	int m_numerator;	// 分子（numerator != 0）
};

Rational::Rational(int d, int n = 1) : m_denominator(d), m_numerator(n){
	if(m_numerator <= 0) throw runtime_error("invalid");
}

Rational::operator double() const{
	return m_denominator / (double)m_numerator;
}

Rational operator+(const Rational& a, const Rational& b){
	int tmp_d = a.denominator() * b.numerator() + b.denominator() * a.numerator();
	int tmp_n = a.numerator() * b.numerator();

	for(int i = tmp_n; i > 1; --i){
		if(tmp_d % i == 0 && tmp_n % i == 0){
			tmp_d /= i;
			tmp_n /= i;
		}
	}

	return Rational(tmp_d, tmp_n);
}

Rational operator-(const Rational& a, const Rational& b){
	return a + Rational(-b.denominator(), b.numerator());
}

Rational operator*(const Rational& a, const Rational& b){
	int tmp_d = a.denominator() * b.denominator();
	int tmp_n = a.numerator() * b.numerator();

	for(int i = tmp_n; i > 1; --i){
		if(tmp_d % i == 0 && tmp_n % i == 0){
			tmp_d /= i;
			tmp_n /= i;
		}
	}

	return Rational(tmp_d, tmp_n);
}

Rational operator/(const Rational& a, const Rational& b){
	int tmp_d = a.denominator() * b.numerator();
	int tmp_n = a.numerator() * b.denominator();

	for(int i = tmp_n; i > 1; --i){
		if(tmp_d % i == 0 && tmp_n % i == 0){
			tmp_d /= i;
			tmp_n /= i;
		}
	}

	return Rational(tmp_d, tmp_n);
}

bool operator==(const Rational& a, const Rational& b){
	if(a.denominator() == b.denominator() && a.numerator() == b.numerator())
		return true;
	return false;
}

bool operator!=(const Rational& a, const Rational& b){
	return !(a == b);
}

int main(){
	Rational r1(10, 4);
	Rational r2(5, 2);

	cout << "r1 = " << r1 << endl;
	cout << "r2 = " << r2 << endl;

	cout << "r1 + r2 = " << (r1 + r2).denominator() << '/' << (r1 + r2).numerator() << " = " << r1 + r2 << endl;
	cout << "r1 - r2 = " << (r1 - r2).denominator() << '/' << (r1 - r2).numerator() << " = " << r1 - r2 << endl;
	cout << "r1 * r2 = " << (r1 * r2).denominator() << '/' << (r1 * r2).numerator() << " = " << r1 * r2 << endl;
	cout << "r1 / r2 = " << (r1 / r2).denominator() << '/' << (r1 / r2).numerator() << " = " << r1 / r2 << endl;
}