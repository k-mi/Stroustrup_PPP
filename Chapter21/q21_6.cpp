#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
using namespace std;

class Date{
public:
	Date() : m_year(1970), m_month(1), m_day(1) { }
	Date(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {
		if(m_year < 1900 || 2100 < m_year) throw runtime_error("invalid year");
		if(m_month < 1 || 12 < m_month) throw runtime_error("invalid month");

		int number_of_days = 31;	// 月の日数
		switch(m_month){
			case 4: case 6: case 9: case 11:
				number_of_days = 30;
				break;
			case 2:
				number_of_days = is_leap() ? 29 : 28;
				break;
			default:
				number_of_days = 31;
				break;
		}
		if(m_day < 1 || number_of_days < d) throw runtime_error("invalid day");
	}

	int year() { return m_year; }
	int month() { return m_month; }
	int day() { return m_day; }

private:
	// うるう年か？
	bool is_leap(){
		return m_year % 400 == 0 || (m_year % 100 != 0 && m_year % 4 == 0);
	}

	int m_year;
	int m_month;
	int m_day;
};

istream& operator>>(istream& is, Date& date){
	if(!is) return is;

	int y, m, d;
	char ch1, ch2;
	cin >> y >> ch1 >> m >> ch2 >> d;
	if(ch1 != '/' || ch2 != '/') return is;

	date = Date(y, m, d);
	return is;
}

ostream& operator<<(ostream& os, Date& d){
	if(!os) return os;
	os << d.year() << '/' << d.month() << '/' << d.day();
	return os;
}

struct Fruit{
	Fruit(const string& n, int c, double up, const Date& d)
		: name(n), count(c), unit_price(up), last_sale_date(d) { }
	//~Fruit() { cout << "Fruit::~Fruit()" << name << endl; }

	string name;
	int count;
	double unit_price;
	Date last_sale_date;
};

// Fruitの代わりにFruit*を使用する。
// 個々のオブジェクトはsetとは別に管理する必要がある。
struct Fruit_comparison{
	bool operator()(const Fruit* a, const Fruit* b) const{
		return a->name < b->name;
	}
};

int main(){
	// オブジェクトはvectorで管理
	vector<Fruit> fruits;
	fruits.push_back(Fruit("Orange", 10, 0.58, Date(2015, 10, 1)));
	fruits.push_back(Fruit("Grape", 1, 3.28, Date(2015, 10, 3)));
	fruits.push_back(Fruit("Plum", 5, 1.15, Date(2015, 10, 2)));
	fruits.push_back(Fruit("Kiwi", 3, 1.99, Date(2015, 10, 7)));
	fruits.push_back(Fruit("Quince", 5, 1.49, Date(2015, 10, 9)));
	fruits.push_back(Fruit("Apple", 3, 0.78, Date(2015, 10, 11)));

	// setにポインタを追加
	set<Fruit*, Fruit_comparison> inventory;
	for(vector<Fruit>::iterator it = fruits.begin(); it != fruits.end(); ++it)
		inventory.insert(&*it);

	// 表示
	for(set<Fruit*, Fruit_comparison>::iterator it = inventory.begin(); it != inventory.end(); ++it)
		cout << (*it)->name << ' ' << (*it)->count << ' ' << (*it)->unit_price << ' ' << (*it)->last_sale_date << endl;
}