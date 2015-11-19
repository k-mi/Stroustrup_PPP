#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	// 接続ポイントを定義するヘルパー関数
	Point n(Circle& c){
		return Point(c.center().x + c.radius() * cos(M_PI / 2), c.center().y - c.radius() * sin(M_PI / 2));
	}

	Point s(Circle& c){
		return Point(c.center().x + c.radius() * cos(3 * M_PI / 2), c.center().y - c.radius() * sin(3 * M_PI / 2));
	}

	Point e(Circle& c){
		return Point(c.center().x + c.radius() * cos(0), c.center().y - c.radius() * sin(0));
	}

	Point w(Circle& c){
		return Point(c.center().x + c.radius() * cos(M_PI), c.center().y - c.radius() * sin(M_PI));
	}

	Point center(Circle& c){
		return Point(c.center().x, c.center().y);
	}

	Point ne(Circle& c){
		return Point(c.center().x + c.radius() * cos(M_PI / 4), c.center().y - c.radius() * sin(M_PI / 4));
	}

	Point se(Circle& c){
		return Point(c.center().x + c.radius() * cos(7 * M_PI / 4), c.center().y - c.radius() * sin(7 * M_PI / 4));
	}

	Point sw(Circle& c){
		return Point(c.center().x + c.radius() * cos(5 * M_PI / 4), c.center().y - c.radius() * sin(5 * M_PI / 4));
	}

	Point nw(Circle& c){
		return Point(c.center().x + c.radius() * cos(3 * M_PI / 4), c.center().y - c.radius() * sin(3 * M_PI / 4));
	}

	Point n(Ellipse& e){
		return Point(e.center().x + e.major() * cos(M_PI / 2), e.center().y - e.minor() * sin(M_PI / 2));
	}

	Point s(Ellipse& e){
		return Point(e.center().x + e.major() * cos(3 * M_PI / 2), e.center().y - e.minor() * sin(3 * M_PI / 2));
	}

	Point e(Ellipse& e){
		return Point(e.center().x + e.major() * cos(0), e.center().y - e.minor() * sin(0));
	}

	Point w(Ellipse& e){
		return Point(e.center().x + e.major() * cos(M_PI), e.center().y - e.minor() * sin(M_PI));
	}

	Point center(Ellipse& e){
		return Point(e.center().x, e.center().y);
	}

	Point ne(Ellipse& e){
		return Point(e.center().x + e.major() * cos(M_PI / 4), e.center().y - e.minor() * sin(M_PI / 4));
	}

	Point se(Ellipse& e){
		return Point(e.center().x + e.major() * cos(7 * M_PI / 4), e.center().y - e.minor() * sin(7 * M_PI / 4));
	}

	Point sw(Ellipse& e){
		return Point(e.center().x + e.major() * cos(5 * M_PI / 4), e.center().y - e.minor() * sin(5 * M_PI / 4));
	}

	Point nw(Ellipse& e){
		return Point(e.center().x + e.major() * cos(3 * M_PI / 4), e.center().y - e.minor() * sin(3 * M_PI / 4));
	}
}


#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "test");

	Circle c(Point(300, 200), 100);
	Graph_lib::Ellipse el(Point(300, 200), 100, 200);

	Open_polyline poly1, poly2;
	poly1.add(n(c));
	poly1.add(s(c));
	poly1.add(e(c));
	poly1.add(w(c));
	poly1.add(center(c));
	poly1.add(ne(c));
	poly1.add(se(c));
	poly1.add(sw(c));
	poly1.add(nw(c));

	poly2.add(n(el));
	poly2.add(s(el));
	poly2.add(e(el));
	poly2.add(w(el));
	poly2.add(center(el));
	poly2.add(ne(el));
	poly2.add(se(el));
	poly2.add(sw(el));
	poly2.add(nw(el));

	win.attach(c);
	win.attach(el);
	win.attach(poly1);
	win.attach(poly2);
	win.wait_for_button();
}