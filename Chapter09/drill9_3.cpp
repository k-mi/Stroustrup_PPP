#include <iostream>
#include <stdexcept>
using namespace std;

// Date型（9.4.3のバージョン）
class Date{
	int y, m, d;				// 年、月、日
public:
	Date(int y, int m, int d);	// 日付の有効性を確認して初期化する
	void add_day(int n);		// Dateをn日増やす
	int month() { return m; }
	int day() { return d; }
	int year() { return y; }
};

// ヘルパー関数:
bool is_date(int y, int m, int d){		// 有効な日付であればtrue
	if(m < 1 || 12 < m) return false;	// 無効な月
	if(d < 1 || 31 < d) return false;	// 無効な日

	return true;
}

ostream& operator<<(ostream& os, Date& d){
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

// メンバ関数:
Date::Date(int y, int m, int d){
	if(!is_date(y, m, d)) throw runtime_error("invalid");

	this->y = y;
	this->m = m;
	this->d = d;
}

void Date::add_day(int n){ // n日増やす
	int y = this->y, m = this->m, d = this->d;
	for(int i = 0; i < n; ++i){
		if(is_date(y, m, d + 1)){
			d++;
		}
		else if(is_date(y, m + 1, 1)){
			m++;
			d = 1;
		}
		else{
			y++;
			d = m = 1;
		}
	}

	this->y = y;
	this->m = m;
	this->d = d;
}	

int main(){
	try{
		Date today(1978, 6, 25);
		cout << today << endl;

		Date tomorrow = today;
		tomorrow.add_day(1);
		cout << tomorrow << endl;

		Date invalid(2004, 13, -5);
		cout << invalid << endl;		
	}
	catch(exception& e){
		cout << "exception: " << e.what() << endl;
	}
}