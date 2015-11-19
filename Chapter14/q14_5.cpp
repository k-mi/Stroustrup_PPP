#include "Graph.h"

namespace Graph_lib{
	class Striped_rectangle : public Rectangle{
	public:
		Striped_rectangle(Point xy, int ww, int hh) : Rectangle(xy, ww, hh) { }
		Striped_rectangle(Point x, Point y) : Rectangle(x, y) { }

		void draw_lines() const;
	};

	void Striped_rectangle::draw_lines() const{
		if(fill_color().visibility()) {    // stripe
			fl_color(fill_color().as_int());
			for(int i = 0; i < height(); i += 3)	// 3ピクセル毎で水平線を描画
				fl_line(point(0).x, point(0).y + i, point(0).x + width(), point(0).y + i);
			fl_color(color().as_int());    // reset color
		}

		if(color().visibility()) {    // lines on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, width(), height());
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Striped_rectangle");

	Striped_rectangle sr(Point(100, 100), 400, 200);
	sr.set_color(Color::blue);
	sr.set_fill_color(Color::black);	// 水平線の色を指定
	sr.set_style(Line_style(Line_style::solid, 5));

	win.attach(sr);
	win.wait_for_button();
}