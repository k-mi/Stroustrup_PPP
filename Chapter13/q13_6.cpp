#define _USE_MATH_DEFINES	// VC++用
#include <cmath>
#include "Graph.h"

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
			cout << angle << endl;
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
	Simple_window win(Point(100, 100), 600, 400, "ClassDiagram");
	
	Vector_ref<Box> boxes;
	Vector_ref<Arrow> arrows;

	boxes.push_back(new Box(Point(50, 50), 100, 30, 10, "Window"));
	boxes.push_back(new Box(Point(200, 50), 100, 30, 10, "Line style"));
	boxes.push_back(new Box(Point(350, 50), 70, 30, 10, "Color"));
	boxes.push_back(new Box(Point(25, 150), 150, 30, 10, "Simple window"));
	boxes.push_back(new Box(Point(400, 150), 70, 30, 10, "Point"));
	boxes.push_back(new Box(Point(240, 120), 70, 30, 10, "Shape"));
	boxes.push_back(new Box(Point(15, 300), 50, 30, 10, "Line"));
	boxes.push_back(new Box(Point(70, 300), 70, 30, 10, "Lines"));
	boxes.push_back(new Box(Point(145, 300), 100, 30, 10, "Polygon"));
	boxes.push_back(new Box(Point(250, 300), 50, 30, 10, "Axis"));
	boxes.push_back(new Box(Point(305, 300), 100, 30, 10, "Rectangle"));
	boxes.push_back(new Box(Point(410, 300), 60, 30, 10, "Text"));
	boxes.push_back(new Box(Point(475, 300), 70, 30, 10, "Image"));

	Arrow a(n(boxes[3]), s(boxes[0]), 10);
	a.set_style(Line_style(Line_style::solid, 3));
	win.attach(a);

	for(int i = 6; i <= 12; ++i){
		arrows.push_back(new Arrow(n(boxes[i]), Point(s(boxes[5]).x - 30 + (i - 6) * 10, s(boxes[5]).y), 10));
		arrows[arrows.size() - 1].set_style(Line_style(Line_style::solid, 3));
		win.attach(arrows[arrows.size() - 1]);
	}

	for(int i = 0; i < boxes.size(); ++i){
		boxes[i].set_style(Line_style(Line_style::solid, 3));
		boxes[i].set_fill_color(Color(220));	// 青
		win.attach(boxes[i]);
	}

	win.wait_for_button();
}