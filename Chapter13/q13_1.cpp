#include "Graph.h"

namespace Graph_lib{
	// 楕円の一部を描画するクラス
	class Arc : public Shape {	 // struct Arc : Shape と同じ意味
	public:
		Arc(Point p, int ww, int hh) 
			: w(ww), h(hh), a1(0), a2(360) { add(Point(p.x - ww, p.y - hh)); }
		Arc(Point p, int ww, int hh, int aa1, int aa2) 
			: w(ww), h(hh), a1(aa1), a2(aa2) { add(Point(p.x - ww, p.y - hh)); }

		void draw_lines() const;
		Point center() const { return Point(point(0).x + w, point(0).y + h); }

		void set_major(int ww) { set_point(0, Point(center().x - ww, center().y - h)); w = ww; }
		int major() const { return w; }
		void set_minor(int hh) { set_point(0, Point(center().x - w, center().y - hh)); h = hh; }
		int minor() const { return h; }

		void set_startangle(int aa1) { a1 = aa1; }
		int stratangle() const { return a1; }
		void set_endangle(int aa2) { a2 = aa2; }
		int endangle() const { return a2; }

	private:
		int w;
		int h;
		int a1;	// 開始角度
		int a2;	// 終了角度
	};

	void Arc::draw_lines() const {
		if(fill_color().visibility()){
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, w + w, h + h, a1, a2);
			fl_color(color().as_int());	// reset color
		}

		if(color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, a1, a2);
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Arc");
	
	Graph_lib::Arc arc1(Point(300, 200), 100, 100, 45, 135);
	Graph_lib::Arc arc2(Point(300, 200), 100, 100, 225, 315);

	arc1.set_fill_color(Color::dark_green);
	arc1.set_color(Color::white);
	arc1.set_style(Line_style(Line_style::solid, 10));

	arc2.set_fill_color(Color::dark_blue);
	arc2.set_color(Color::white);
	arc2.set_style(Line_style(Line_style::solid, 10));

	win.attach(arc1);
	win.attach(arc2);
	win.wait_for_button();
}