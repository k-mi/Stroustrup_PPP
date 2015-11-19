#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Striped_circle : public Circle{
	public:
		Striped_circle(Point p, int rr) : Circle(p, rr) { }

		void draw_lines() const;
	};

	void Striped_circle::draw_lines() const{
		if(fill_color().visibility()) {    // stripe
			fl_color(fill_color().as_int());

			for(int i = radius(); i >= -radius(); i -= 3){	// 3ドットずつ水平線を描画
				fl_line(center().x - radius() * cos(asin(double(i) / radius())), center().y + i,
						center().x + radius() * cos(asin(double(i) / radius())), center().y + i);
			}

			fl_color(color().as_int());    // reset color
		}

		if(color().visibility()) {    // lines on top of fill
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, radius() + radius(), radius() + radius(), 0, 360);
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Striped_rectangle");

	Striped_circle sc(Point(300, 200), 150);
	sc.set_color(Color::blue);
	sc.set_fill_color(Color::cyan);	// 水平線の色を指定
	sc.set_style(Line_style(Line_style::solid, 5));

	win.attach(sc);
	win.wait_for_button();
}