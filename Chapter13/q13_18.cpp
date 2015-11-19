#include "Graph.h"

namespace Graph_lib{
	class Poly : public Polygon{
	public:
		Poly(Point a, Point b, Point c){
			Polygon::add(a);
			Polygon::add(b);
			Polygon::add(c);
		}

		void add(Point p) { Polygon::add(p); }
		void draw_lines() const { Polygon::draw_lines(); }
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Poly");

	Poly p(Point(100, 300), Point(200, 350), Point(300, 100));
	p.add(Point(300, 50));

	win.attach(p);
	win.wait_for_button();
}