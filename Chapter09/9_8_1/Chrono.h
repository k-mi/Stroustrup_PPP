#include <iostream>
using namespace std;

namespace Chrono{
	class Date{
	public:
		enum Month{
			jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
		};

		class Invalid {};				// 例外としてスローする

		Date(int yy, Month mm, int dd);	// 日付の有効性を確認して初期化する
		Date();							// デフォルトコンストラクタ
		// デフォルトのコピー操作でOK

		// 非変更操作:
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		// 変更操作:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int y;
		Month m;
		int d;
	};

	bool is_date(int y, Date::Month d, int d);	// 日付が有効である場合はtrue

	bool leapyear(int y);						// yがうるう年である場合はtrue

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);

	istream& operator>>(istream& is, Date& d);
}	// Chrono