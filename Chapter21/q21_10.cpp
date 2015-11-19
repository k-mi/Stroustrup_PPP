#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>
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
	is >> y >> ch1 >> m >> ch2 >> d;
	if(ch1 != '/' || ch2 != '/') return is;

	date = Date(y, m, d);
	return is;
}

ostream& operator<<(ostream& os, Date& d){
	if(!os) return os;
	os << d.year() << '/' << d.month() << '/' << d.day();
	return os;
}

struct Purchase{
	Purchase(const string& n, double up, int c) 
		: name(n), unit_price(up), count(c) { }

	string name;				// 商品名
	double unit_price;			// 単価
	int count;					// 数量
};

struct Order{
	Order() { }
	Order(const string& n, const string& a, const Date& d, const vector<Purchase>& vp)
		: name(n), address(a), date(d), purchase(vp) { }

	string name;				// 顧客の名前
	string address;				// 住所
	Date date;					// 日付（注文日）
	vector<Purchase> purchase;	// 購入情報
};

// ファイルから（push_back）を持つコンテナへのデータの追加
// 入力は、顧客の名前、住所、日付と各購入情報を1行ずつで表す
// 購入情報は、商品名、単価、数量の順にカンマ区切りで表す
// 空行で各Orderの入力終了
template<class T> void file_input(T& container, const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) return;

	string name;
	string address;
	Date date;
	vector<Purchase> purchase;

	string line;
	int kind = 0;
	while(getline(ifs, line)){
		switch(kind){
			case 0:
				name = line;
				break;
			case 1:
				address = line;
				break;
			case 2:
			{
				istringstream iss(line);
				iss >> date;
				break;
			}
			default:
			{
				istringstream iss(line);
				char ch;

				if(!(iss >> ch)){
					container.push_back(Order(name, address, date, purchase));				
					purchase.clear();
					kind = -1;
				}
				else{
					iss.unget();
					string n = "";
					double up;
					int c;

					while(iss >> ch && ch != ',') n += ch;
					if(n == "") break;
					iss >> up >> ch >> c;
					if(ch != ',') break;

					purchase.push_back(Purchase(n, up, c));						
				}
				break;			
			}
		}
		++kind;
	}		
}

// コンテナからファイルへ出力
template<class Iter> void file_output(Iter first, Iter last, const string& filename){
	ofstream ofs(filename);
	if(!ofs) return;

	while(first != last){
		ofs << first->name << endl;
		ofs << first->address << endl;
		ofs << first->date << endl;

		for(int i = 0; i < first->purchase.size(); ++i){
			ofs << first->purchase[i].name << ", " 
				<< first->purchase[i].unit_price << ", " 
				<< first->purchase[i].count << endl;
		}

		ofs << endl;
		++first;		
	}
}

struct Sort_by_name{
	bool operator()(const Order& o1, const Order& o2){
		return o1.name < o2.name;
	}
};

struct Sort_by_address{
	bool operator()(const Order& o1, const Order& o2){
		return o1.address < o2.address;
	}
};

// q21_10
// 合計金額を返す
template<class Iter> double sum(Iter first, Iter last){
	double money = 0;

	while(first != last){
		for(int i = 0; i < first->purchase.size(); ++i)
			money += first->purchase[i].unit_price * first->purchase[i].count;
		++first;
	}

	return money;
}

int main(){
	// q21_9
	// リストを読み込み顧客の名前でソート
	vector<Order> v_order;
	file_input(v_order, "q21_9_input1.txt");
	sort(v_order.begin(), v_order.end(), Sort_by_name());
	file_output(v_order.begin(), v_order.end(), "q21_9_output1.txt");

	// 別のリストを読み込み顧客の住所でソート
	list<Order> l_order;
	file_input(l_order, "q21_9_input2.txt");
	l_order.sort(Sort_by_address());
	file_output(l_order.begin(), l_order.end(), "q21_9_output2.txt");

	// q21_10
	cout << "sum: " << sum(v_order.begin(), v_order.end()) + sum(l_order.begin(), l_order.end()) << endl;
}