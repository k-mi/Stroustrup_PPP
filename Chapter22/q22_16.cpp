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

	class Arrow : public Shape {
	public:
		Arrow(Point p1, Point p2, int ll) : l(ll) {
			add(p1);
			add(p2);
			if(l < 0) error("Bad arrow: negative arrow length");
		}

		void draw_lines() const;

	private:
		int l;	// 矢の長さ
	};

	void Arrow::draw_lines() const {
		if(color().visibility()) {
			double angle = atan2(point(1).x - point(0).x, -(point(1).y - point(0).y)) + M_PI / 2;
			fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
			fl_line(point(1).x, point(1).y, point(1).x + l * cos(M_PI / 4 + angle), point(1).y + l * sin(M_PI / 4 + angle));
			fl_line(point(1).x, point(1).y, point(1).x + l * cos(7 * M_PI / 4 + angle), point(1).y + l * sin(7 * M_PI / 4 + angle));
		}
	}

	class Ellipse_text : public Ellipse {
	public:
		Ellipse_text(Point point, int height, string t)
			: Ellipse(point, height, height / 2.5), text(t) { }

		void draw_lines() const;

	private:
		string text;	// 楕円の中に表示するテキスト
	};

	void Ellipse_text::draw_lines() const {
		Ellipse::draw_lines();

		Text t(Point(point(0).x, point(0).y + minor() * 1.5), " " + text);
		t.set_font_size(minor());
		t.draw();
	}
}

struct Plang {
	Plang() : name(""), year(-1) { }
	Plang(const string& n, int y, const vector<string>& a) : name(n), year(y), ancestor(a) { }

	string name;				// 言語名
	int year;					// 登場年
	vector<string> ancestor;	// 祖先
};

// 入力フォーマット: (name, year(ancestor1, ...)) ただし1900<=year<=2015
istream& operator>>(istream& is, Plang& p) {
	if(!is) return is;

	string name = "";
	int year;
	char tmp, ch1, ch2, ch3, ch4;
	vector<string> vs;

	is >> ch1;
	if(ch1 != '(') return is;

	while(is >> tmp && tmp != ',') name += tmp;	// カンマを1つ吸収
	if(name == "") return is;
	is >> year >> ch2 >> ch3;
	if(year < 1900 || 2015 < year || ch2 != ',' || ch3 != '(') return is;

	string s = "";
	while(is >> tmp && tmp != ')') {
		if(tmp == ',') {
			if(s != "") vs.push_back(s);
			s = "";
		}
		else s += tmp;
	}
	if(s != "") vs.push_back(s);

	is >> ch4;
	if(ch4 != ')') return is;

	p = Plang(name, year, vs);
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

	const string filename = "q22_16_input.txt";	// 入力ファイル名
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
	Simple_window win(Point(100, 100), 1280, 400, "Programming language");
	const int elli_height = 40;										// 楕円の高さ
	const int space = 20;											// 周囲の空白
	const int crevice = elli_height;								// 要素間の隙間
	const int width = win.x_max() - space * 2 - elli_height * 2;	// グラフの幅
	const int height = win.y_max() - space * 2 - elli_height;		// グラフの高さ
	const int max_line = height / elli_height;						// 行数
	vector<int> before_position(max_line, -(elli_height + crevice * 2));	// 行ごとの1つ前の楕円のx座標を保持

	Vector_ref<Ellipse_text> elements;	// 要素を格納
	Vector_ref<Shape> shapes;			// その他の図形を格納

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
		et->set_fill_color(Color::yellow);
		elements.push_back(et);
		win.attach(elements[elements.size() - 1]);

		// 矢印
		for(vector<string>::const_iterator it2 = it->ancestor.begin(); it2 != it->ancestor.end(); ++it2) {
			for(int i = 0; i < elements.size(); ++i) {
				if(list[i].name == *it2) {
					Arrow* a = new Arrow(Point(elements[i].center().x + elli_height, elements[i].center().y), Point(et->point(0).x, et->point(0).y + elli_height / 2), 10);
					a->set_style(Line_style(Line_style::solid, 3));
					shapes.push_back(a);
					win.attach(shapes[shapes.size() - 1]);
					break;
				}
			}
		}
	}

	for(int i = 0; i < elements.size(); ++i)
		win.attach(elements[i]);

	win.wait_for_button();
}