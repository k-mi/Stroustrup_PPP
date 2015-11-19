#include <cmath>
#include "Graph.h"
#define M_PI (acos(-1))

namespace Graph_lib{
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
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Arrow");

	Arrow a1(Point(100, 300), Point(50, 300), 10);
	a1.set_color(Color::blue);
	a1.set_style(Line_style(Line_style::solid, 5));

	Arrow a2(Point(100, 50), Point(200, 350), 25);
	a2.set_color(Color::red);
	a2.set_style(Line_style(Line_style::solid, 5));

	win.attach(a1);
	win.attach(a2);
	win.wait_for_button();
}