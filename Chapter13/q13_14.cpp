#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	// 直角三角形のクラス
	class Right_triangle : public Polygon{
	public:
		Right_triangle(Point a, Point b, Point c){
			add(a);
			add(b);
			add(c);

			// 最も長い辺が斜辺
			// 斜辺の長さの2乗とそれ以外の辺の長さの2乗の和とが等しくなれば直角三角形
			double l1 = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
			double l2 = sqrt((b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y));
			double l3 = sqrt((c.x - a.x) * (c.x - a.x) + (c.y - a.y) * (c.y - a.y));

			// 小数点以下の誤差を考慮して、±1ドットを許容
			if(l1 > l2 && l1 > l3){			// a-b
				if(l1 - 1 > sqrt(l2 * l2 + l3 * l3) || sqrt(l2 * l2 + l3 * l3) > l1 + 1) error("bad right triangle");
			}
			else if(l2 > l1 && l2 > l3){	// b-c
				if(l2 - 1 > sqrt(l1 * l1 + l3 * l3) || sqrt(l1 * l1 + l3 * l3) > l2 + 1) error("bad right triangle");
			}
			else if(l3 > l1 && l3 > l2){	// c-a
				if(l3 - 1 > sqrt(l1 * l1 + l2 * l2) || sqrt(l1 * l1 + l2 * l2) > l3 + 1) error("bad right triangle");
			}
			else{
				error("bad right triangle");
			}
		}

		void drow_lines() const { Polygon::draw_lines(); }
	};
}

#include "Simple_window.h"
int main(){
	Simple_window win(Point(100, 100), 600, 400, "Right triangle");
	Vector_ref<Right_triangle> vr;

	const double angle = M_PI / 4;			// 八角形の内角
	const int o_radius = 200;				// 中心から外側の角までの距離
	const int i_radius = 83;				// 中心から内側の角までの距離
	const int x = 300, y = 200;				// 中心座標

	for(int i = 0; i < 8; ++i){
		Point p1(x + o_radius * cos(i * angle), y - o_radius * sin(i * angle));
		Point p2(x + o_radius * cos((i + 1) * angle), y - o_radius * sin((i + 1) * angle));
		Point p3(x + i_radius * cos((i + 2) * angle), y - i_radius * sin((i + 2) * angle));

		vr.push_back(new Right_triangle(p1, p2, p3));
		vr[vr.size() - 1].set_fill_color(Color(i));
		win.attach(vr[vr.size() - 1]);
	}

	win.wait_for_button();
}