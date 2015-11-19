#include <iostream>
#include <stdexcept>
using namespace std;

// Date型（9.4.1のバージョン）
struct Date{
	int y;	// 年
	int m;	// 月
	int d;	// 日
};

// ヘルパー関数:
bool is_date(int y, int m, int d){		// 有効な日付であればtrue
	if(m < 1 || 12 < m) return false;	// 無効な月
	if(d < 1 || 31 < d) return false;	// 無効な日

	return true;
}

// (y,m,d)が有効な日付かどうか確認し、そうである場合はddを初期化する
void init_day(Date& dd, int y, int m, int d){
	if(!is_date(y, m, d)) throw runtime_error("invalid");

	dd.y = y;
	dd.m = m;
	dd.d = d;
}

// ddをn日増やす
void add_day(Date& dd, int n){
	int y = dd.y, m = dd.m, d = dd.d;
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

	dd.y = y;
	dd.m = m;
	dd.d = d;
}

ostream& operator<<(ostream& os, const Date& d){
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main(){
	try{
		Date today;
		init_day(today, 1978, 6, 25);
		cout << today << endl;

		Date tomorrow = today;
		add_day(tomorrow, 1);
		cout << tomorrow << endl;

		Date invalid;
		init_day(invalid, 2004, 13, -5);
		cout << invalid << endl;		
	}
	catch(exception& e){
		cout << "exception: " << e.what() << endl;
	}
}