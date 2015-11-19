#include <iostream>
#include <vector>
#include <stdexcept>
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
	int m_y;	// 年
	Month m_m;	// 月
	int m_d;	// 日
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

	enum Genre{
		fiction, nonfiction, periodical, biography, children
	};

	// コンストラクタ
	Book(Isbn isbn, string title, string author, Date publication, Genre genre);

	void lend();		// 貸し出し
	void ret();			// 返却

	Isbn isbn() const { return m_isbn; }
	string title() const { return m_title; }
	string author() const { return m_author; }
	Date publication() const { return m_publication; }
	Genre genre() const { return m_genre; }

private:
	Isbn m_isbn;		// ISBN
	string m_title;		// タイトル
	string m_author;	// 著者
	Date m_publication;	// 出版日
	Genre m_genre;		// ジャンル

	bool m_loan;		// 貸し出しされていればtrue
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

Date::Date() : m_y(2001), m_m(jan), m_d(1) { }

Date::Date(int y, Month m, int d) : m_y(y), m_m(m), m_d(d){
	if(!is_date(m_y, m_m, m_d)) throw runtime_error("invalid: Date");
}

Book::Book(Isbn isbn, string title, string author, Date publication, Genre genre)
	: m_isbn(isbn), m_title(title), m_author(author), m_publication(publication), m_genre(genre), m_loan(false)
{
	if(isbn.m_c == '!') throw runtime_error("invalid: Isbn");
	if(genre < fiction || children < genre)  throw runtime_error("invalid: Genre");
}

void Book::lend(){
	if(m_loan == true)
		cout << "すでに貸し出されています。" << endl;
	m_loan = true;
}

void Book::ret(){
	if(m_loan == false)
		cout << "すでに返却されています。" << endl;
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

bool operator==(const Book& b1, const Book& b2){
	if(b1.isbn().m_group == b2.isbn().m_group && b1.isbn().m_a == b2.isbn().m_a
		&& b1.isbn().m_b == b2.isbn().m_b && b1.isbn().m_c == b2.isbn().m_c) return true;

	return false;
}

bool operator!=(const Book& b1, const Book& b2){
	return !(b1 == b2);
}

ostream& operator<<(ostream& os, const Book& book){
	os << "Title: " << book.title() << endl 
	   << "Author: " << book.author() << endl
	   << "ISBN: " << book.isbn().m_group << '-' << book.isbn().m_a << '-' << book.isbn().m_b << '-' << book.isbn().m_c << endl;

	return os;
}

class Patron{
public:
	Patron(string name, int id, int charge = 0) : m_name(name), m_id(id), m_charge(charge) { }

	string get_name() const { return m_name; }
	int get_id() const { return m_id; }
	int get_charge() const { return m_charge; }

	void set_charge(int n) {
		if(n < 0) runtime_error("invalid: charge");
		m_charge = n;
	} 

private:
	string m_name;	// 利用者の名前
	int m_id;		// 図書館カードの番号
	int m_charge;		// 利用料
};

bool operator==(const Patron& p1, const Patron& p2){
	if(p1.get_id() == p2.get_id() && p1.get_name() == p2.get_name() && p1.get_charge() == p2.get_charge()) return true;

	return false;
}

bool operator!=(const Patron& p1, const Patron& p2){
	return !(p1 == p2);
}

// Patronのヘルパー関数: 利用料を支払う場合はtrue
bool is_charge(const Patron& p){
	return p.get_charge() == 0 ? false : true;
}

class Library{
public:
	struct Transaction{
		Transaction(Book b, Patron p, Date d) : book(b), patron(p), date(d) { }

		Book book;
		Patron patron;
		Date date;
	};

	void add_book(const Book& b);				// 図書館に本を追加
	void add_patron(const Patron& p);			// 図書館に利用者を追加
	void loan(Book& b, const Patron& p);		// 本を貸し出す

	vector<Book> books() const { return dic_book; }
	vector<Patron> patrons() const { return dic_patron; }
	vector<Transaction> transactions() const { return dic_transaction; }

private:
	vector<Book> dic_book;
	vector<Patron> dic_patron;
	vector<Transaction> dic_transaction;
};

void Library::add_book(const Book& b){
	dic_book.push_back(b);
}

void Library::add_patron(const Patron& p){
	dic_patron.push_back(p);
}

void Library::loan(Book& b, const Patron& p){
	for(int i = 0; i < dic_book.size(); ++i){
		if(dic_book[i] == b)
			break;
		if(i == dic_book.size() - 1) throw runtime_error(b.title() + "という本は存在しません。");
	}
	for(int i = 0; i < dic_patron.size(); ++i){
		if(dic_patron[i] == p)
			break;
		if(i == dic_patron.size() - 1) throw runtime_error(p.get_name() + "という利用者は存在しません。");
	}
	
	if(is_charge(p)) throw runtime_error(p.get_name() + "は利用料を支払う必要があります。");
	b.lend();	// 貸し出し
	dic_transaction.push_back(Transaction(b, p, Date(2015, Date::aug, 28)));
}

// 利用料を支払う利用者を返す
vector<string> charge_patron(Library& l){
	vector<string> names;
	for(int i = 0; i < l.patrons().size(); ++i){
		if(is_charge(l.patrons()[i]))
			names.push_back(l.patrons()[i].get_name());
	}
	return names;
}

int main(){
	Library library;

	Book::Isbn isbn;
	string title, author;
	Date publication;
	int genre;

	cout << "本を追加" << endl;
	for(int i = 0; i < 3; ++i){
		cout << "isbn(\"group-a-b-c\") > ";
		cin >> isbn;
		cout << "title > ";
		cin >> title;
		cout << "author > ";
		cin >> author;
		cout << "publication day(\"(year,month,day)\") > ";
		cin >> publication;
		cout << "genre(0:fiction, 1:nonfiction, 2:periodical, 3:biography, 4:children) > ";
		cin >> genre;

		library.add_book(Book(isbn, title, author, publication, Book::Genre(genre)));		
	}

	string name;
	int id, charge;

	cout << "利用者を追加" << endl;
	for(int i = 0; i < 3; ++i){
		cout << "name > ";
		cin >> name;
		cout << "id > ";
		cin >> id;
		cout << "charge > ";
		cin >> charge;

		library.add_patron(Patron(name, id, charge));		
	}

	library.loan(library.books()[0], library.patrons()[1]);
	library.loan(library.books()[0], library.patrons()[2]);
	library.loan(library.books()[0], Patron("ABC", 12345678, 0));
}