#include <iostream>
#include <stdexcept>
using namespace std;

// Date型（9.7.1のバージョン）
class Date{
public:
	enum Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	Date(int y, Month m, int d);	// 日付の有効性を確認して初期化する
	void add_day(int n);			// Dateをn日増やす
	Month month() { return m; }
	int day() { return d; }
	int year() { return y; }

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

bool is_date(int y, Date::Month m, int d){	// 有効な日付であればtrue
	int days_in_month = 31;		// 月の最大日数

	switch(m){
		case Date::feb:
			days_in_month = leapyear(y) ? 29 : 28;
			break;
		case Date::apr:
		case Date::jun:
		case Date::sep:
		case Date::nov:
			days_in_month = 30;
			break;
		default:
			days_in_month = 31;
	}

	if(m < Date::jan || Date::dec < m) return false;	// 無効な月
	if(d < 1 || days_in_month < d) return false;		// 無効な日

	return true;
}

ostream& operator<<(ostream& os, Date& d){
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

// メンバ関数:
Date::Date(int y, Month m, int d){
	if(!is_date(y, m, d)) throw runtime_error("invalid");

	this->y = y;
	this->m = m;
	this->d = d;
}

void Date::add_day(int n){ // n日増やす
	int y = this->y, d = this->d;
	Month m = this->m;

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

	this->y = y;
	this->m = m;
	this->d = d;
}	

int main(){
	try{
		Date today(1978, Date::jun, 25);
		cout << today << endl;

		Date tomorrow = today;
		tomorrow.add_day(1);
		cout << tomorrow << endl;

		Date invalid(2005, Date::feb, 29);
		cout << invalid << endl;		
	}
	catch(exception& e){
		cout << "exception: " << e.what() << endl;
	}
}