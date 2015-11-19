#include "Graph.h"

namespace Graph_lib{
	// 丸角四角形を描画するクラス
	class Box : public Shape {
	public:
		Box(Point xy, int ww, int hh, int rr) : w(ww), h(hh), r(rr)
		{
			add(xy);
			if(h <= 0 || w <= 0 || r <= 0) error("Bad box: non-positive width, height, radius");
		}

		Box(Point x, Point y, int rr) : w(y.x - x.x), h(y.y - x.y), r(rr)
		{
			add(x);
			if(h <= 0 || w <= 0 || r <= 0) error("Bad box: non-positive width, height, radius");
		}

		void draw_lines() const;

		int height() const { return h; }
		int width() const { return w; }
		int radius() const { return r; }
	private:
		int h;
		int w;
		int r;	// 角の半径
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
	}

	class Pseudo_window : public Box{
	public:
		Pseudo_window(Point xy, int w, int h, const string& title, const string& pic = "../image1.jpg")
			: Box(xy, w, h, 5),
			label(Point(xy.x + 5, xy.y + 20), title),
			im(Point(xy.x + 5, xy.y + 30), pic),
			line(Point(xy.x, xy.y + 24), Point(xy.x + w, xy.y + 24)),
			ctrl(Point(xy.x + w - 21, xy.y + 2), 21, 21, 5),
			x(Point(xy.x + w - 16, xy.y + 18), "x")
		{
			set_style(Line_style(Line_style::solid, 3));
			line.set_style(Line_style(Line_style::solid, 3));
			im.set_mask(Point(0, 0), w - 10, h - 35);
			ctrl.set_fill_color(Color::red);
			ctrl.set_color(Color::invisible);
			x.set_font_size(24);
		}

		void draw_lines() const;

	private:
		Text label;
		Line line;
		Box ctrl;
		Text x;
		Image im;
	};

	void Pseudo_window::draw_lines() const{
		Box::draw_lines();
		label.draw();
		line.draw();
		ctrl.draw();
		x.draw();
		im.draw();
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Window");

	Pseudo_window pw1(Point(50, 50), 300, 150, "Window1");
	Pseudo_window pw2(Point(400, 200), 150, 150, "Window2");
	Pseudo_window pw3(Point(100, 250), 200, 100, "Window3");

	win.attach(pw1);
	win.attach(pw2);
	win.attach(pw3);
	win.wait_for_button();
}