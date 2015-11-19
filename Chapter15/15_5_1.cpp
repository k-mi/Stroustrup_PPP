#include "Graph.h"
#include "Simple_window.h"

int fac(int n)	// factorial(n) : n!
{
	int r = 1;
	while(n > 1){
		r *= n;
		--n;
	}
	return r;
}

double term(double x, int n) { return pow(x, n) / fac(n); }	// 数列のn番目の項

double expe(double x, int n)	// xのn個の項の合計
{
	double sum = 0;
	for(int i = 0; i < n; i++) sum += term(x, i);
	return sum;
}

int expN_number_of_terms = 10;

double expN(double x)
{
	return expe(x, expN_number_of_terms);
}

int main(){
	const int xmax = 600;			// ウインドウサイズ
	const int ymax = 400;

	const int x_orig = xmax / 2;	// 位置(0, 0)はウインドウの中心
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	const int r_min = -10;			// 範囲[-10:11)
	const int r_max = 11;

	const int n_points = 400;		// 範囲内で使用されるポイントの数

	const int x_scale = 30;			// 倍率
	const int y_scale = 30;

	Simple_window win(Point(100, 100), xmax, ymax, "exp");

	const int xlength = xmax - 40;	// ウインドウよりも少し小さい軸を作成する
	const int ylength = ymax - 40;

	Axis x(Axis::x, Point(20, y_orig), xlength, xlength / x_scale, "one notch == 1");
	Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, ylength / y_scale, "one notch == 1");
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Function real_exp(exp, r_min, r_max, orig, 200, x_scale, y_scale);
	real_exp.set_color(Color::blue);
	win.attach(real_exp);
	win.wait_for_button();

	for(int n = 0; n < 50; ++n){
		ostringstream ss;
		ss << "exp approximation: n==" << n;
		win.set_label(ss.str());
		expN_number_of_terms = n;
		// 次の近似値を取得する
		Function e(expN, r_min, r_max, orig, 200, x_scale, y_scale);
		win.attach(e);
		win.wait_for_button();
		win.detach(e);
	}
}