#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

// Date型（9.7.4のバージョン）
class Date{
public:
	enum Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	Date(int y, Month m, int d);	// 日付の有効性を確認して初期化する
	
	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }

	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

private:
	int y;		// 年
	Month m;	// 月
	int d;		// 日
};

// ヘルパー関数:
bool leapyear(int y){	// うるう年であればtrue
	if(y % 4 == 0 && y % 100 != 0) return true;
	if(y % 400 == 0) return true;
	return false;
}

int days_in_month(int y, Date::Month m){
	switch(m){
		case Date::feb:
			return leapyear(y) ? 29 : 28;
		case Date::apr:
		case Date::jun:
		case Date::sep:
		case Date::nov:
			return 30;
		default:
			return 31;
	}
}

bool is_date(int y, Date::Month m, int d){	// 有効な日付であればtrue
	if(m < Date::jan || Date::dec < m) return false;	// 無効な月
	if(d < 1 || days_in_month(y, m) < d) return false;		// 無効な日

	return true;
}

ostream& operator<<(ostream& os, const Date& d){
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

// メンバ関数:
Date::Date(int y, Month m, int d){
	if(!is_date(y, m, d)) throw runtime_error("invalid");

	this->y = y;
	this->m = m;
	this->d = d;
}

void Date::add_day(int n){
	for(int i = 0; i < n; ++i){
		if(is_date(y, m, d + 1)){
			d++;
		}
		else if(m + 1 <= dec){
			m = Month(m + 1);
			d = 1;
		}
		else{
			y++;
			d = 1;
			m = jan;
		}
	}

	assert(is_date(y, m, d));
}

void Date::add_month(int n){
	for(int i = 0; i < n; ++i){
		if(m + 1 <= dec){
			m = Month(m + 1);
		}
		else{
			m = jan;
			y++;
		}
	}

	if(days_in_month(y, m) < d){
		d -= days_in_month(y, m);
		add_month(1);
	}

	assert(is_date(y, m, d));
}

void Date::add_year(int n){
	y += n;

	if(!leapyear(y) && m == feb && d == 29){
		m = mar;
		d = 1;
	}

	assert(is_date(y, m, d));
}	

int main(){
	try{
		Date today(1978, Date::jun, 25);
		cout << today << endl;

		Date tomorrow = today;
		tomorrow.add_day(1);
		cout << tomorrow << endl;

		tomorrow.add_day(4);
		cout << tomorrow << endl;
		tomorrow.add_month(20);
		cout << tomorrow << endl;

		Date invalid(2005, Date::feb, 29);
		cout << invalid << endl;		
	}
	catch(exception& e){
		cout << "exception: " << e.what() << endl;
	}
}