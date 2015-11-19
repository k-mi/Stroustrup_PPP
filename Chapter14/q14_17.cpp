#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	// 丸角四角形を描画するクラス
	class Box : public Shape {
	public:
		Box(Point xy, int ww, int hh, int rr, const string& s = "") : w(ww), h(hh), r(rr), lab(s), fnt(fl_font()), fnt_sz(fl_size())
		{
			add(xy);
			if(h <= 0 || w <= 0 || r <= 0) error("Bad box: non-positive width, height, radius");
		}

		Box(Point x, Point y, int rr, const string& s = "") : w(y.x - x.x), h(y.y - x.y), r(rr), lab(s), fnt(fl_font()), fnt_sz(fl_size())
		{
			add(x);
			if(h <= 0 || w <= 0 || r <= 0) error("Bad box: non-positive width, height, radius");
		}

		void draw_lines() const;

		int height() const { return h; }
		int width() const { return w; }
		int radius() const { return r; }

		void set_label(const string& s) { lab = s; }
		string label() const { return lab; }

		void set_font(Font f) { fnt = f; }
		Font font() const { return Font(fnt); }

		void set_font_size(int s) { fnt_sz = s; }
		int font_size() const { return fnt_sz; }

	private:
		int h;
		int w;
		int r;		// 角の半径
		string lab; // ラベルテキスト
		Font fnt;	// フォント
		int fnt_sz;	// フォントサイズ
	};

	void Box::draw_lines() const{
		if(fill_color().visibility()) {    // fill
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x + r, point(0).y, w - r - r, h);								// 丸角四角形内の縦の長方形
			fl_rectf(point(0).x, point(0).y + r, w, h - r - r);								// 丸角四角形内の横の長方形
			fl_pie(point(0).x + w - r - r, point(0).y, r + r, r + r, 0, 90);				// 右上円
			fl_pie(point(0).x, point(0).y, r + r, r + r, 90, 180);							// 左上円
			fl_pie(point(0).x, point(0).y + h - r - r, r + r, r + r, 180, 270);				// 左下円
			fl_pie(point(0).x + w - r - r, point(0).y + h - r - r, r + r, r + r, 270, 360);	// 右下円
			fl_color(color().as_int());    // reset color
		}

		if(color().visibility()) {    // lines on top of fill
			fl_color(color().as_int());
			fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);			// 上線
			fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);	// 下線
			fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);			// 左線
			fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);	// 右線
			fl_arc(point(0).x + w - r - r, point(0).y, r + r, r + r, 0, 90);				// 右上角丸
			fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);							// 左上角丸
			fl_arc(point(0).x, point(0).y + h - r - r, r + r, r + r, 180, 270);				// 左下角丸
			fl_arc(point(0).x + w - r - r, point(0).y + h - r - r, r + r, r + r, 270, 360);	// 右下角丸
		}

		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(), fnt_sz);
		fl_draw(lab.c_str(), point(0).x + r, point(0).y + h - r);
		fl_font(ofnt, osz);
	}

	class Arrow : public Shape{
	public:
		Arrow(Point p1, Point p2, int ll) : l(ll){
			add(p1);
			add(p2);
			if(l < 0) error("Bad arrow: negative arrow length");
		}

		void draw_lines() const;

	private:
		int l;	// 矢の長さ
	};

	void Arrow::draw_lines() const{
		if(color().visibility()){
			double angle = atan2(point(1).x - point(0).x, -(point(1).y - point(0).y)) + M_PI / 2;
			fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
			fl_line(point(1).x, point(1).y, point(1).x + l * cos(M_PI / 4 + angle), point(1).y + l * sin(M_PI / 4 + angle));
			fl_line(point(1).x, point(1).y, point(1).x + l * cos(7 * M_PI / 4 + angle), point(1).y + l * sin(7 * M_PI / 4 + angle));
		}
	}

	// 接続ポイントを定義するヘルパー関数
	Point n(Box& b){
		return Point(b.point(0).x + b.width() / 2, b.point(0).y);
	}

	Point s(Box& b){
		return Point(b.point(0).x + b.width() / 2, b.point(0).y + b.height());
	}

	Point e(Box& b){
		return Point(b.point(0).x + b.width(), b.point(0).y + b.height() / 2);
	}

	Point w(Box& b){
		return Point(b.point(0).x, b.point(0).y + b.height() / 2);
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 1280, 720, "Exception ClassDiagram");

	Vector_ref<Box> boxes;
	Vector_ref<Arrow> arrows;

	boxes.push_back(new Box(Point(590, 20), 100, 30, 10, "exception"));
	
	// exception
	boxes.push_back(new Box(Point(200, 150), 110, 30, 10, "logic_error"));
	boxes.push_back(new Box(Point(320, 150), 130, 30, 10, "runtime_error"));
	boxes.push_back(new Box(Point(460, 150), 110, 30, 10, "bad_typeid"));
	boxes.push_back(new Box(Point(580, 150), 90, 30, 10, "bad_cast"));
	boxes.push_back(new Box(Point(680, 150), 130, 30, 10, "bad_weak_ptr"));
	boxes.push_back(new Box(Point(820, 150), 100, 30, 10, "bad_alloc"));
	boxes.push_back(new Box(Point(930, 150), 140, 30, 10, "bad_exception"));

	// logic_error
	boxes.push_back(new Box(Point(0, 300), 160, 30, 10, "invalid_argument"));
	boxes.push_back(new Box(Point(165, 300), 115, 30, 10, "domain_error"));
	boxes.push_back(new Box(Point(285, 300), 115, 30, 10, "length_error"));
	boxes.push_back(new Box(Point(405, 300), 115, 30, 10, "out_of_range"));
	boxes.push_back(new Box(Point(525, 300), 110, 30, 10, "future_error"));

	// runtime_error
	boxes.push_back(new Box(Point(640, 300), 100, 30, 10, "range_error"));
	boxes.push_back(new Box(Point(745, 300), 120, 30, 10, "overflow_error"));
	boxes.push_back(new Box(Point(890, 300), 140, 30, 10, "underflow_error"));
	boxes.push_back(new Box(Point(1035, 300), 110, 30, 10, "regex_error"));
	boxes.push_back(new Box(Point(1150, 300), 120, 30, 10, "system_error"));

	// bad_alloc
	boxes.push_back(new Box(Point(770, 350), 200, 30, 10, "bad_array_new_length"));

	// system_error
	boxes.push_back(new Box(Point(1110, 450), 160, 30, 10, "ios_base::failure"));

	for(int i = 1; i <= 7; ++i){
		arrows.push_back(new Arrow(n(boxes[i]), Point(s(boxes[0]).x - 10 + (i - 3.5) * 10, s(boxes[0]).y), 10));
		arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
		win.attach(arrows[arrows.size() - 1]);
	}

	for(int i = 8; i <= 12; ++i){
		arrows.push_back(new Arrow(n(boxes[i]), Point(s(boxes[1]).x - 80 + (i - 2.5) * 10, s(boxes[1]).y), 10));
		arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
		win.attach(arrows[arrows.size() - 1]);
	}

	for(int i = 13; i <= 17; ++i){
		arrows.push_back(new Arrow(n(boxes[i]), Point(s(boxes[2]).x - 130 + (i - 2.5) * 10, s(boxes[2]).y), 10));
		arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
		win.attach(arrows[arrows.size() - 1]);
	}

	arrows.push_back(new Arrow(n(boxes[18]), Point(s(boxes[6]).x, s(boxes[6]).y), 10));
	arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
	win.attach(arrows[arrows.size() - 1]);

	arrows.push_back(new Arrow(n(boxes[19]), Point(s(boxes[17]).x, s(boxes[17]).y), 10));
	arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
	win.attach(arrows[arrows.size() - 1]);

	for(int i = 0; i < boxes.size(); ++i){
		boxes[i].set_style(Line_style(Line_style::solid, 3));
		boxes[i].set_fill_color(Color(220));	// 青
		win.attach(boxes[i]);
	}

	win.wait_for_button();
}