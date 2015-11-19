#include <cmath>
#include "Simple_window.h"
#include "Graph.h"

#define M_PI (acos(-1))

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Ellipse");

	Point center(300, 200);
	Graph_lib::Ellipse e(center, 150, 100);

	Axis ax(Axis::x, Point(center.x - 200, center.y), 400, 10);
	Axis ay(Axis::y, Point(center.x, center.y + 150), 300, 10);

	Mark f1(e.focus1(), 'x');		// 焦点
	Mark f2(e.focus2(), 'x');

	const double angle = M_PI / 4;	// どちらかの軸上にない楕円上のポイント
	Point p(e.center().x + e.major() * cos(angle), e.center().y - e.minor() * sin(angle));
	Mark fp(p, 'x');
	
	Line l1(e.focus1(), p);
	Line l2(e.focus2(), p);

	win.attach(e);
	win.attach(ax);
	win.attach(ay);
	win.attach(f1);
	win.attach(f2);
	win.attach(fp);
	win.attach(l1);
	win.attach(l2);

	win.wait_for_button();
}