#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Regular_polygon : public Polygon{
	public:
		Regular_polygon(Point pp, int rr, int nn) : p(pp)
		{
			r = rr;
			if(r <= 0) error("Bad polygon: non-positive radius length");
			n = nn;
			if(n < 3) error("Bad polygon: less than 3 sides");

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
		int n;		// 辺の数
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Regular_polygon");

	Regular_polygon p1(Point(300, 200), 100, 8);
	Regular_polygon p2(Point(300, 200), 120, 20);

	win.attach(p1);
	win.attach(p2);
	win.wait_for_button();
}