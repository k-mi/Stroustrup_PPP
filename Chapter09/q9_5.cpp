#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;

class Date{
public:
	enum Month{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	Date();							// デフォルトコンストラクタ
	Date(int y, Month m, int d);	// 日付の有効性を確認して初期化する
	
	int day() const { return m_d; }
	Month month() const { return m_m; }
	int year() const { return m_y; }

private:
	int m_y;		// 年
	Month m_m;		// 月
	int m_d;		// 日
};

class Book{
public:
	struct Isbn
	{
		Isbn() : m_group(0), m_a(0), m_b(0), m_c('!') {}
		Isbn(int group, int a, int b, char c) : m_group(group), m_a(a), m_b(b), m_c(c) {}

		int m_group;	// グループ記号
		int m_a;		// 出版社記号
		int m_b;		// 書名記号
		char m_c;		// チェックディジット		
	};

	// コンストラクタ
	Book(Isbn isbn, string title, string author, Date publication)
		: m_isbn(isbn), m_title(title), m_author(author), m_publication(publication), m_loan(false){}

	void lend();		// 貸し出し
	void ret();			// 返却

	Isbn isbn() { return m_isbn; }
	string title() { return m_title; }
	string author() { return m_author; }
	Date publication() { return m_publication; }

private:
	Isbn m_isbn;		// ISBN
	string m_title;		// タイトル
	string m_author;	// 著者
	Date m_publication;	// 出版日

	bool m_loan;		// 貸し出し
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

ostream& operator<<(ostream& os, const Date& d){
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

istream& operator>>(istream& is, Date& dd){
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

Date::Date() : m_y(2001), m_m(jan), m_d(1) {

}

Date::Date(int y, Month m, int d) : m_y(y), m_m(m), m_d(d){
	if(!is_date(m_y, m_m, m_d)) throw runtime_error("invalid");
}

void Book::lend(){
	if(m_loan == true)
		throw runtime_error("すでに貸し出されています。");

	m_loan = true;
}

void Book::ret(){
	if(m_loan == false)
		throw runtime_error("すでに返却されています。");

	m_loan = false;
}

istream& operator>>(istream& is, Book::Isbn& isbn){
	char c1, c2, c3, c;
	int group, a, b;

	is >> group >> c1 >> a >> c2 >> b >> c3 >> c;
	if(!is) return is;
	if(c1 != '-' || c2 != '-' || c3 != '-'){	// 書式エラー
		is.clear(ios_base::failbit);
		return is;
	}
	isbn = Book::Isbn(group, a, b, c);
	return is;
}

int main(){
	Book::Isbn isbn;
	string title, author;
	Date publication;
	// 入力
	cout << "isbn(\"group-a-b-c\") > ";
	cin >> isbn;
	cout << "title > ";
	cin >> title;
	cout << "author > ";
	cin >> author;
	cout << "publication day(\"(year,month,day)\") > ";
	cin >> publication;

	Book book(isbn, title, author, publication);

	book.lend();
	book.ret();
}