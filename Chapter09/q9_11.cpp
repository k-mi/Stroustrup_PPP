#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

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