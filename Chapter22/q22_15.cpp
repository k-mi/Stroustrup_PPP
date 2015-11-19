#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

namespace Graph_lib {
	const double M_PI = acos(-1);	// 円周率

	class Ellipse_text : public Ellipse {
	public:
		Ellipse_text(Point point, int height, string t)
			: Ellipse(point, height, height / 2), text(t) { }

		void draw_lines() const;

	private:
		string text;	// 楕円の中に表示するテキスト
	};

	void Ellipse_text::draw_lines() const{
		Ellipse::draw_lines();

		Text t(Point(point(0).x, point(0).y + minor() * 1.5), text);
		t.set_font_size(minor());
		t.draw();
	}
}

struct Plang {
	Plang() : name(""), year(-1) { }
	Plang(string n, int y) : name(n), year(y) { }

	string name;	// 言語名
	int year;		// 登場年
};

// 入力フォーマット: (name, year) ただし1900<=year<=2015
istream& operator>>(istream& is, Plang& p) {
	if(!is) return is;
	
	string s = "";
	int y;
	char tmp, ch1, ch2;

	is >> ch1;
	if(ch1 != '(') return is;

	while(is.get(tmp) && tmp != ',') s += tmp;	// カンマを1つ吸収
	if(s == "") return is;
	is >> y >> ch2;
	if(y < 1900 || 2015 < y || ch2 != ')') return is;

	p = Plang(s, y);
	return is;
}

// yearで比較
struct Comp_year {
	bool operator()(const Plang& p1, const Plang& p2) {
		return p1.year < p2.year;
	}
};

// 年からx座標を算出
int year_position(int year, int width, int min, int max) {
	return (year - min) * (width / (max - min));
}

int main()
{
	using namespace Graph_lib;

	const string filename = "q22_15_input.txt";	// 入力ファイル名
	ifstream ifs(filename.c_str());

	vector<Plang> list;							// 入力データ
	Plang tmp;
	int year_min = 2015, year_max = 1900;		// 入力された年の最小値、最大値
											
	while(ifs >> tmp) {
		list.push_back(tmp);
		if(year_min > tmp.year) year_min = tmp.year;
		if(year_max < tmp.year) year_max = tmp.year;
	}
	if(list.size() == 0) return 1;

	sort(list.begin(), list.end(), Comp_year());

	// 作成するウインドウ、グラフのパラメータ
	Simple_window win(Point(100, 100), 1000, 400, "Programming language");
	const int elli_height = 40;										// 楕円の高さ
	const int space = 20;											// 周囲の空白
	const int crevice = elli_height * 1.5;							// 要素間の隙間
	const int width = win.x_max() - space * 2 -	elli_height * 2;		// グラフの幅
	const int height = win.y_max() - space * 2 - elli_height;		// グラフの高さ
	const int max_line = height / elli_height;						// 行数
	vector<int> before_position(max_line, -(elli_height+crevice*2));	// 行ごとの1つ前の楕円のx座標を保持

	Vector_ref<Shape> shapes;	// 図形（のポインタ）を格納
	
	// 目盛りの描画
	for(int i = year_min; i < year_max + 5; i += 5) {
		while(i % 5 != 0) ++i;
		int x = year_position(i, width, year_min, year_max);
		shapes.push_back(new Line(Point(space + elli_height + x, space), Point(space + elli_height + x, space + height)));
		win.attach(shapes[shapes.size() - 1]);
		shapes.push_back(new Text(Point(space + elli_height + x - 20, space + height + 20), to_string(i)));
		win.attach(shapes[shapes.size() - 1]);
	}
	
	// 要素の描画
	for(vector<Plang>::const_iterator it = list.begin(); it != list.end(); ++it) {
		int x = year_position(it->year, width, year_min, year_max);
		int line;
		for(line = 0; line < max_line; ++line) {
			if(before_position[line] + elli_height + crevice * 2 <= x) break;
		}
		if(line == max_line) line = 0;
		before_position[line] = x;

		Ellipse_text* et = new Ellipse_text(Point(space + elli_height + x, space + elli_height / 2 + line * elli_height), elli_height, it->name);
		et->set_fill_color(Color::dark_cyan);
		shapes.push_back(et);
		win.attach(shapes[shapes.size() - 1]);
	}

	win.wait_for_button();
}