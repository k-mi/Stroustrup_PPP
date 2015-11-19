#include "GUI.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Date {
public:
	Date() : m_year(1970), m_month(1), m_day(1) { }
	Date(int y, int m, int d) : m_year(y), m_month(m), m_day(d) {
		if(m_year < 1900 || 2100 < m_year) throw runtime_error("invalid year");
		if(m_month < 1 || 12 < m_month) throw runtime_error("invalid month");

		int number_of_days = 31;	// 月の日数
		switch(m_month) {
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
	bool is_leap() {
		return m_year % 400 == 0 || (m_year % 100 != 0 && m_year % 4 == 0);
	}

	int m_year;
	int m_month;
	int m_day;
};

istream& operator>>(istream& is, Date& date) {
	if(!is) return is;

	int y, m, d;
	char ch1, ch2;
	is >> y >> ch1 >> m >> ch2 >> d;
	if(ch1 != '/' || ch2 != '/') return is;

	date = Date(y, m, d);
	return is;
}

ostream& operator<<(ostream& os, Date& d) {
	if(!os) return os;
	os << d.year() << '/' << d.month() << '/' << d.day();
	return os;
}

struct Purchase {
	Purchase() { }
	Purchase(const string& n, double up, int c)
		: name(n), unit_price(up), count(c) { }

	string name;				// 商品名
	double unit_price;			// 単価
	int count;					// 数量
};

istream& operator>>(istream& is, Purchase& p) {
	if(!is) return is;

	string n = "";
	double up;
	int c;

	char ch;
	while(is >> ch && ch != ',') n += ch;
	if(n == "") return is;
	is >> up >> ch >> c;
	if(ch != ',') return is;

	p = Purchase(n, up, c);
	return is;
}

struct Order {
	Order() { }
	Order(const string& n, const string& a, const Date& d, const vector<Purchase>& vp)
		: name(n), address(a), date(d), purchase(vp) { }

	string name;				// 顧客の名前
	string address;				// 住所
	Date date;					// 日付（注文日）
	vector<Purchase> purchase;	// 購入情報
};

// ファイルから（push_back）を持つコンテナへのデータの追加
template<class T> void file_input(T& container, const string& filename) {
	ifstream ifs(filename.c_str());
	if(!ifs) return;

	string name;
	string address;
	Date date;
	vector<Purchase> purchase;

	string line;
	int kind = 0;
	while(getline(ifs, line)) {
		switch(kind) {
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

				if(!(iss >> ch)) {
					container.push_back(Order(name, address, date, purchase));
					purchase.clear();
					kind = -1;
				}
				else {
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

// strとOrderのnameが一致しているかを返す関数オブジェクト
class Pred_name {
public:
	Pred_name(string str) : s(str) { }
	bool operator()(const Order& order) {
		if(s == "") return true;	// 何も指定されていない場合は全てtrueを返す
		return s == order.name; 
	}
private:
	string s;
};

namespace Graph_lib {
	class Orderlist_window : public Graph_lib::Window {
	public:
		Orderlist_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			inbox_ifile(Point(120, 10), x_max() - 250, 30, "input filename:"),
			inbox_name(Point(120, 40), x_max() - 250, 30, "search(name):"),
			outbox_total(Point(x_max() - 200, y_max() - 40), 180, 30, "total:"),
			button_enter(Point(x_max() - 110, 25), 90, 30, "enter", cb_enter),
			text_y(90), orderlist(nullptr)
		{
			attach(inbox_ifile);
			attach(inbox_name);
			attach(outbox_total);
			attach(button_enter);
		}

	private:
		In_box inbox_ifile;				// 入力ファイル名
		In_box inbox_name;				// （検索する）名前
		
		Out_box outbox_total;			// 合計金額
		Button button_enter;
		Vector_ref<Text>* orderlist;	// 注文リスト: ここに検索結果の注文を追加

		vector<Order> order;
		double total;
		int text_y;

		static void cb_enter(Address, Address pw) { reference_to<Orderlist_window>(pw).enter(); }
		
		// 注文をリストアップする
		void enter() {
			// 初期化
			total = 0;
			order.clear();
			if(orderlist != nullptr) {
				for(int i = 0; i < orderlist->size(); ++i) 
					detach((*orderlist)[i]);
				delete orderlist;
			}
			orderlist = new Vector_ref<Text>;

			file_input(order, inbox_ifile.get_string());

			int i = 0;	// テキストの行番号
			vector<Order>::iterator it = order.begin();
			while(true) {
				it = find_if(it, order.end(), Pred_name(inbox_name.get_string()));
				if(it == order.end()) break;

				vector<Purchase>& vp = it->purchase;
				for(vector<Purchase>::iterator iter = vp.begin(); iter != vp.end(); ++iter) {
					ostringstream oss;
					oss << iter->name << "(" << iter->unit_price << ") x " << iter->count;
					orderlist->push_back(new Text(Point(10, text_y + 20 * i), oss.str()));

					total += iter->unit_price * iter->count;
					++i;
				}
				++it;
			}

			for(int i = 0; i < orderlist->size(); ++i)
				attach((*orderlist)[i]);

			outbox_total.put(to_string(total));
			Fl::redraw();	// 再描画
		}
	};
}

int main() {
	using namespace Graph_lib;

	Orderlist_window win(Point(100, 100), 600, 400, "Order list");
	gui_main();
}