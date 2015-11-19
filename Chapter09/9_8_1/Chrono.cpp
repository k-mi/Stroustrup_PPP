#include "Chrono.h"
#include <iostream>
using namespace std;

namespace Chrono{
	// メンバ変数の定義:
	Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd){
		if(!is_date(y, m, d)) throw Invalid();
	}

	const Date& default_date(){
		static Date dd(2001, Date::jan, 1);	// 21世紀最初の日
		return dd;
	}

	Date::Date() : y(default_date().y), m(default_date().m), d(default_date().d) {}
	// Date::Date() : Date(default_date()) {}	// なぜ使えない？

	void Date::add_day(int n){
		// ...
	}
	void Date::add_month(int n){
		// ...
	}
	void Date::add_year(int n){
		// うるう年に注意 2月29日の代わりに3月1日を使用
		if(m == fab && d == 29 && !leapyear(y + n)){
			m = mar;
			d = 1;
		}
		y += n;
	}

	// ヘルパー変数:
	bool is_date(int y, Date::Month m, int d){
		// yは有効である前提とする
		if(d <= 0) return false;	// dは正の数でなければならない
		if(m < Date::jan || Date::dec < m) return false;

		int days_in_month = 31;		// 月の最大日数は31

		switch(m){
			case Date::feb:			// 2月の日数は年による
				days_in_month = (leapyear(y)) ? 29 : 28;
				break;

			case Date::apr:
			case Date::jun:
			case Date::sep:
			case Date::nov:
				days_in_month = 30;
				break;
		}

		if(days_in_month < d) return false;

		dd = Date(y, Date::Month(m), d);	// ddを更新（必要？）
		return true;
	}

	bool leapyear(int y){
		// 練習問題10を参照
	}

	bool operator==(const Date& a, const Date& b){
		return a.year() == b.year() 
			&& a.month() == b.month()
			&& a.day() && b.day();
	}

	bool operator!=(const Date& a, const Date& b){
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& dd){
		return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& d){
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if(!is) return is;
		if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')'){	// 書式エラー
			is.clear(ios_base::failbit);	// failbitを設定する
			return is;
		}
		dd = Date(y, Date::Month(m), d);
		return is;
	}

	enum Day{
		sunday, monday, tuesday, wednesday, thrsday, friday, saturday
	};

	Day day_of_week(const Date& d){
		// ...
	}

	Date next_Sunday(const Date& d){
		// ...
	}

	Date next_weekday(const Date& d){
		// ...
	}
}