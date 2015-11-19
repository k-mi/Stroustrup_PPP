﻿#include <cmath>
#include "Graph.h"

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

	const int interval = 50;
	for(int x = 0; x < win.x_max(); x += interval){
		for(int y = 0; y < win.y_max(); y += interval * 2){
			vr.push_back(new Right_triangle(Point(x, y), Point(x + interval, y), Point(x, y + interval * 2)));
			vr[vr.size() - 1].set_style(Line_style(Line_style::solid, 2));
			win.attach(vr[vr.size() - 1]);

			vr.push_back(new Right_triangle(Point(x + interval, y), Point(x, y + interval * 2), Point(x + interval, y + interval * 2)));
			vr[vr.size() - 1].set_style(Line_style(Line_style::solid, 2));
			win.attach(vr[vr.size() - 1]);
		}
	}

	win.wait_for_button();
}