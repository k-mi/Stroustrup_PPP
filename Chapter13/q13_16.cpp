#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

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

	Vector_ref<Regular_hexagon> vhex;
	const int r = 50;	// 六角形の中心から角までの距離

	for(int i = 0; (i * r * sqrt(3) / 2) <= win.y_max(); ++i){
		for(int j = 0; (j * r * 3) <= win.x_max(); ++j){
			if(i % 2 == 0)
				vhex.push_back(new Regular_hexagon(Point(j * r * 3, i * r * sqrt(3) / 2), r));
			else
				vhex.push_back(new Regular_hexagon(Point(j * r * 3 + r * 3 / 2, i * r * sqrt(3) / 2), r));
			vhex[vhex.size() - 1].set_style(Line_style(Line_style::solid, 3));
			vhex[vhex.size() - 1].set_color(Color::yellow);
			win.attach(vhex[vhex.size() - 1]);
		}
	}

	win.wait_for_button();
}