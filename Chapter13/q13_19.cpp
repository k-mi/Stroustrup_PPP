#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Star : public Polygon{
	public:
		Star(Point pp, int nn, int or, int ir, int off = 0) 
			: p(pp), n(nn), o_radius(or), i_radius(ir), offset_angle(off){

			if(n < 4 || o_radius <= 0 || i_radius <= 0 || o_radius <= i_radius) error("Bad star");

			const double angle = 2 * M_PI / n;	// 内角
			const double offset = offset_angle == 0 ? 0 : 360 / (2 * M_PI * offset_angle);

			for(double i = 0, oa = offset, ia = offset + angle / 2; i < n; ++i, oa += angle, ia += angle){
				Polygon::add(Point(p.x + o_radius * cos(oa), p.y - o_radius * sin(oa)));	// 外側
				Polygon::add(Point(p.x + i_radius * cos(ia), p.y - i_radius * sin(ia)));	// 内側
			}
		}

		void draw_lines() const { Polygon::draw_lines(); }

	private:
		Point p;			// 中心座標
		int n;				// ポイントの数（n >= 4）
		int o_radius;		// 外側の点までの距離
		int i_radius;		// 内側の点までの距離
		int offset_angle;	// 回転
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Star");

	Star s1(Point(300, 200), 5, 200, 100, -60);
	s1.set_fill_color(Color::yellow);

	Star s2(Point(50, 100), 8, 50, 20);
	s2.set_color(Color::blue);
	s2.set_style(Line_style(Line_style::solid, 5));

	win.attach(s1);
	win.attach(s2);
	win.wait_for_button();
}