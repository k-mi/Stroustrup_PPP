#include "Graph.h"
#include "Simple_window.h"

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }

int main(){
	using namespace Graph_lib;

	const int xmax = 600;		// ウインドウサイズ
	const int ymax = 600;

	const int xorig = xmax / 2;	// 原点
	const int yorig = ymax / 2;
	const Point orig(xorig, yorig);

	const int xscale = 20;
	const int yscale = 20;

	const int xoffset = 100;	// ウインドウの左端からy軸までの距離
	const int yoffset = 100;	// ウインドウの下端からx軸までの距離

	const int xlength = 400;	// 軸の長さ
	const int ylength = 400;

	const int r_min = -10;
	const int r_max = 11;

	Simple_window win(Point(100, 100), xmax, ymax, "Function graphs");

	Axis x(Axis::x, Point(xoffset, yorig), xlength, xscale, "1==20pixels");
	Axis y(Axis::y, Point(xorig, ymax - yoffset), ylength, yscale, "1==20pixels");
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Function f1(one, r_min, r_max, orig, 400, 1, 1);
	win.attach(f1);
	win.wait_for_button();

	Function f2(one, r_min, r_max, orig, 400, xscale, yscale);
	win.attach(f2);
	win.wait_for_button();

	Function f3(slope, r_min, r_max, orig, 400, xscale, yscale);
	win.attach(f3);
	win.wait_for_button();

	Text t3(Point(f3.point(0).x, f3.point(0).y - 20), "x/2");
	win.attach(t3);
	win.wait_for_button();

	Function f4(square, r_min, r_max, orig, 400, xscale, yscale);
	win.attach(f4);
	win.wait_for_button();

	Function f5(cos, r_min, r_max, orig, 400, xscale, yscale);
	win.attach(f5);
	win.wait_for_button();
}