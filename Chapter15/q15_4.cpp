#include "Graph.h"
#include "Simple_window.h"

double sincos(double x) { return sin(x) + cos(x); }
double square_sincos(double x) { return sin(x) * sin(x) + cos(x) * cos(x); }

int main(){
	const int xmax = 600;			// ウインドウサイズ
	const int ymax = 400;

	const int x_orig = xmax / 2;	// 位置(0, 0)はウインドウの中心
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	const int xlength = xmax - 40;	// ウインドウよりも少し小さい軸を作成する
	const int ylength = ymax - 40;

	const int scale = 30;			// 倍率

	const int r_min = -10;			// 範囲[-10:11)
	const int r_max = 11;

	Simple_window win(Point(100, 100), xmax, ymax, "q15_4");

	Axis x(Axis::x, Point(20, y_orig), xlength, xlength / scale);
	Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, ylength / scale);
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Function f1(sin, r_min, r_max, orig, 400, scale, scale);
	Text t1(Point(f1.point(0).x, f1.point(0).y), "sin(x)");
	f1.set_color(Color::blue);
	t1.set_color(Color::blue);
	win.attach(f1);
	win.attach(t1);

	Function f2(cos, r_min, r_max, orig, 400, scale, scale);
	Text t2(Point(f2.point(0).x, f2.point(0).y + 20), "cos(x)");
	f2.set_color(Color::magenta);
	t2.set_color(Color::magenta);
	win.attach(f2);
	win.attach(t2);

	Function f3(sincos, r_min, r_max, orig, 400, scale, scale);
	Text t3(Point(f3.point(0).x, f3.point(0).y), "sin(x)+cos(x)");
 	win.attach(f3);
	win.attach(t3);

	Function f4(square_sincos, r_min, r_max, orig, 400, scale, scale);
	Text t4(Point(f4.point(0).x, f4.point(0).y - 10), "sin(x)*sin(x)+cos(x)*cos(x)");
	win.attach(f4);
	win.attach(t4);

	win.wait_for_button();
}