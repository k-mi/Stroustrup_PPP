#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

class Date{
public:
	enum Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	Date() : m_d(0){ }				// 初期値
	Date(long int d);				// 1970年1月1日からの日数
	Date(int y, Month m, int d);	// 年月日
	
	int day() const;
	Month month() const;
	int year() const;
	long int raw() const { return m_d; }

	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

private:
	long int m_d;		// 1970年1月1日からの日数
};

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
	if(y < 1970) return false;							// 無効な年
	if(m < Date::jan || Date::dec < m) return false;	// 無効な月
	if(d < 1 || days_in_month(y, m) < d) return false;	// 無効な日

	return true;
}

bool is_date(int d){	// 有効な日付であればtrue
	if(d < 0) return false;

	return true;
}

// メンバ関数:
Date::Date(long int d) : m_d(d){
	if(!is_date(m_d)) throw runtime_error("invalid");
}

Date::Date(int y, Month m, int d){
	if(!is_date(y, m, d)) throw runtime_error("invalid");

	Date tmp;
	tmp.add_year(y-1970);
	tmp.add_month(m-1);
	tmp.add_day(d-1);

	if(!is_date(tmp.raw())) throw runtime_error("invalid");
	m_d = tmp.raw();
}

int Date::day() const{
	int year = 1970;
	Month month = jan;
	long int raw = m_d;

	while(raw / (leapyear(year) ? 366 : 365) > 0){
		raw -= leapyear(year) ? 366 : 365;
		year++;
	}

	while(raw / days_in_month(year, month) > 0){
		raw -= days_in_month(year, month);	
		month = Month(month + 1);
	}

	return raw + 1;
}

Date::Month Date::month() const{
	int year = 1970;
	Month month = jan;
	long int raw = m_d;

	while(raw / (leapyear(year) ? 366 : 365) > 0){
		raw -= leapyear(year) ? 366 : 365;
		year++;
	}

	while(raw / days_in_month(year, month) > 0){
		raw -= days_in_month(year, month);
		month = Month(month + 1);
	}

	return Month(month);	
}

int Date::year() const{
	int year = 1970;
	long int raw = m_d;

	while(raw / (leapyear(year) ? 366 : 365) > 0){
		raw -= leapyear(year) ? 366 : 365;
		year++;
	}

	return year;
}

void Date::add_day(int n){
	m_d += n;

	if(!is_date(n)) throw runtime_error("invalid: add");
}

void Date::add_month(int n){
	for(int i = 0; i < n; ++i)
		m_d += days_in_month(this->year(), this->month());

	if(!is_date(n)) throw runtime_error("invalid: add");
}

void Date::add_year(int n){
	for(int i = 0; i < n; ++i){
		if(leapyear(this->year()))
			m_d += 366;
		else
			m_d += 365;
	}

	if(!is_date(n)) throw runtime_error("invalid: add");
}	

// ヘルパー関数:
ostream& operator<<(ostream& os, const Date& d){
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

enum Day{
	sunday, monday, tuesday, wednesday, thrsday, friday, saturday
};

Day day_of_week(const Date& d){
	int c = d.year() / 100;
	int y = d.year() % 100;
	int m = d.month();

	if(d.month() == Date::jan || d.month() == Date::feb){
		c = (d.year() - 1) / 100;
		y = (d.year() - 1) % 100;
		m += 12;
	}

	int gamma = d.year() >= 1582 ? (5 * c + c / 4) : (6 * c + 5);
	return Day((d.day() + (26 * (m + 1)) / 10 + y + y / 4 + gamma + 6) % 7);
}

// 次の平日を求める
Date next_weekday(const Date& d){
	Date tmp = d;
	tmp.add_day(1);
	while(day_of_week(tmp) == sunday || day_of_week(tmp) == saturday)
		tmp.add_day(1);
	return tmp;
}

// 元日を含む週を1とした場合のdの週を求める
int week_of_year(const Date& d){
	int week = 1;
	Date tmp(d.year(), Date::jan, 1);

	while(tmp.day() != d.day() || tmp.month() != d.month()){
		tmp.add_day(1);
		if(day_of_week(tmp) == sunday)
			week++;
	}

	return week;
}

int main(){
	try{
		Date today(2015, Date::aug, 28);
		cout << "today: " << today << endl;

		Date tomorrow = today;
		tomorrow.add_day(1);
		cout << "tomorrow: " << tomorrow << endl;

		cout << "day_of_week: " << day_of_week(today) << endl;
		cout << "next_weekday: " << next_weekday(today) << endl;
		cout << "week_of_year: " << week_of_year(today) << endl;
	}
	catch(exception& e){
		cout << "exception: " << e.what() << endl;
	}
}