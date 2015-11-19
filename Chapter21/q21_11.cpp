#include "GUI.h"
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
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

// 複数のstringからPurchaseにデータを格納
void read_purchase(const vector<string>& vs, vector<Purchase>& vp) {
	for(int i = 0; i < vs.size(); ++i) {
		if(vs[i] == "") continue;

		Purchase p, q;
		istringstream iss(vs[i]);
		iss >> p;
		
		vp.push_back(p);
	}
}

// コンテナからファイルへ出力
template<class Iter> void file_output(Iter first, Iter last, const string& filename) {
	ofstream ofs(filename);
	if(!ofs) return;

	while(first != last) {
		ofs << first->name << endl;
		ofs << first->address << endl;
		ofs << first->date << endl;

		for(int i = 0; i < first->purchase.size(); ++i) {
			ofs << first->purchase[i].name << ", "
				<< first->purchase[i].unit_price << ", "
				<< first->purchase[i].count << endl;
		}

		ofs << endl;
		++first;
	}
}

namespace Graph_lib {
	// Order入力用ウインドウ
	class Order_window : public Graph_lib::Window {
	public:
		Order_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			inbox_name(Point(120, 50), x_max() - 200, 30, "Name:"),
			inbox_address(Point(120, 80), x_max() - 200, 30, "Address:"),
			inbox_date(Point(120, 110), x_max() - 200, 30, "Date:"),
			inbox_purchase1(Point(120, 170), x_max() - 200, 30, "Purchase1:"),
			inbox_purchase2(Point(120, 200), x_max() - 200, 30, "Purchase2:"),
			inbox_purchase3(Point(120, 230), x_max() - 200, 30, "Purchase3:"),
			inbox_purchase4(Point(120, 260), x_max() - 200, 30, "Purchase4:"),
			inbox_purchase5(Point(120, 290), x_max() - 200, 30, "Purchase5:"),
			button_next(Point(x_max() - 100, y_max() - 40), 90, 30, "Next", cb_next),
			button_save(Point(x_max() - 200, y_max() - 40), 90, 30, "Save", cb_save),
			text_order(Point(80, 30), "Order: 1"),
			text_exam(Point(120, 340), "Purchase: product_name, unit_price, amount"),
			count(1)
		{
			attach(inbox_name);
			attach(inbox_address);
			attach(inbox_date);
			attach(inbox_purchase1);
			attach(inbox_purchase2);
			attach(inbox_purchase3);
			attach(inbox_purchase4);
			attach(inbox_purchase5);
			attach(button_next);
			attach(button_save);
			attach(text_order);
			attach(text_exam);
			text_exam.set_font_size(14);
		}

	private:
		// 顧客情報
		In_box inbox_name;		// 名前
		In_box inbox_address;	// 住所
		In_box inbox_date;		// 日付
		
		// 商品（最大5つまで入力できる）
		In_box inbox_purchase1;
		In_box inbox_purchase2;
		In_box inbox_purchase3;
		In_box inbox_purchase4;
		In_box inbox_purchase5;
		
		Button button_next;
		Button button_save;

		Text text_order;
		Text text_exam;

		static void cb_next(Address, Address pw) { reference_to<Order_window>(pw).next(); }
		static void cb_save(Address, Address pw) { reference_to<Order_window>(pw).save(); }

		vector<Order> order;
		int count;

		// orderに格納して次の入力へ
		void next() {
			string name = inbox_name.get_string();
			string address = inbox_address.get_string();
			Date date;
			istringstream d(inbox_date.get_string());
			d >> date;
			
			vector<string> vs;
			vs.push_back(inbox_purchase1.get_string());
			vs.push_back(inbox_purchase2.get_string());
			vs.push_back(inbox_purchase3.get_string());
			vs.push_back(inbox_purchase4.get_string());
			vs.push_back(inbox_purchase5.get_string());
			vector<Purchase> purchase;
			read_purchase(vs, purchase);

			order.push_back(Order(name, address, date, purchase));

			++count;
			text_order.set_label("Order: " + to_string(count));
			Fl::redraw();	// 再描画
		}

		// orderをファイルに保存して終了
		void save() {
			next();	// orderに格納

			const string filename = "q21_11_output.txt";	// 保存先
			file_output(order.begin(), order.end(), filename);
			exit(EXIT_SUCCESS);
		}
	};
}

int main() {
	using namespace Graph_lib;

	Order_window win(Point(100, 100), 600, 400, "Order to file");
	gui_main();
}