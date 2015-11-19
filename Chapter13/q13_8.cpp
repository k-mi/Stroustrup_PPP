#define _USE_MATH_DEFINES	// VC++用
#include <cmath>
#include "Graph.h"

namespace Graph_lib{
	class Regular_hexagon : public Polygon{
	public:	
		Regular_hexagon(Point pp, int rr) : p(pp) 
		{
			r = rr;
			if(r <= 0) error("Bad hexagon: non-positive radius length");

			const int n = 6;	// 六角形
			double angle = 0;
			for(int i = 0; i < n; ++i) {
				add(Point(p.x + r * cos(angle), p.y - r * sin(angle)));
				angle += 2 * M_PI / n;
			}
		}

		void draw_lines() const { Polygon::draw_lines(); }

		Point center() { return p; }
		int radius() { return r; }

	private:
		Point p;	// 中心座標
		int r;		// 中心から角までの距離
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Hexagon");

	Regular_hexagon hex(Point(300, 200), 100);

	win.attach(hex);
	win.wait_for_button();
}