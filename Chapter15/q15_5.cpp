#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

double real(double x) { return M_PI / 4; }

int number_of_terms;
double leibniz(double x){
	double tmp = 0;
	for(int i = 1; i <= number_of_terms; ++i){
		if(i % 2 == 1) tmp += 1.0 / (i * 2 - 1);
		else tmp -= 1.0 / (i * 2 - 1);
	}
	return tmp;
}

namespace Graph_lib{
	// 引数を格納し、リセット可能なFunctionクラス
	class Funct : public Shape{	// "Fuc"の名前がすでに定義済みだったため、"Funct"クラスとする
	public:
		Funct(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25) :
			m_f(f), m_r1(r1), m_r2(r2), m_orig(orig), m_count(count), m_xscale(xscale), m_yscale(yscale)
		{
			if(m_r2 - m_r1 <= 0) error("bad graphing range");
			if(m_count <= 0) error("non-positive graphing count");
		}

		void draw_lines() const{
			double dist = (m_r2 - m_r1) / m_count;
			double r = m_r1;
			Open_polyline op;
			for(int i = 0; i < m_count; ++i) {
				op.add(Point(m_orig.x + int(r * m_xscale), m_orig.y - int(m_f(r)*m_yscale)));
				r += dist;
			}
			op.draw_lines();
		}

		// 関数と範囲を変更
		void reset(Fct f, double r1, double r2) {
			if(r2 - r1 <= 0) error("bad graphing range");

			m_f = f;
			m_r1 = r1;
			m_r2 = r2;
		}

	private:
		Fct *m_f;			// 関数ポインタ
		double m_r1;		// 範囲 [m_r1:m_r2)
		double m_r2;
		Point m_orig;		// 原点
		int m_count;		// 使用される点の数
		double m_xscale;	// 倍率
		double m_yscale;
	};
}

#include "Simple_window.h"

int main(){
	const int xmax = 600;			// ウインドウサイズ
	const int ymax = 400;

	const int x_orig = xmax / 2;	// 原点
	const int y_orig = ymax / 2;
	const Point orig(x_orig, y_orig);

	const int xlength = xmax - 40;	// ウインドウよりも少し小さい軸を作成する
	const int ylength = ymax - 40;

	const int scale = 150;			// 倍率

	const int r_min = -2;			// 範囲
	const int r_max = 2;

	Simple_window win(Point(100, 100), xmax, ymax, "Fct");

	Axis x(Axis::x, Point(20, y_orig), xlength, xlength / scale);
	Axis y(Axis::y, Point(x_orig, ylength + 20), ylength, ylength / scale);
	x.set_color(Color::red);
	y.set_color(Color::red);
	win.attach(x);
	win.attach(y);

	Funct real_leibniz(real, r_min, r_max, orig, 50, scale, scale);
	real_leibniz.set_color(Color::blue);
	win.attach(real_leibniz);

	Funct approx_leibniz(leibniz, r_min, r_max, orig, 50, scale, scale);
	win.attach(approx_leibniz);

	for(int i = 0; i < 50; ++i){
		number_of_terms = i;
		approx_leibniz.reset(leibniz, r_min, r_max);
		win.set_label("Leibniz: " + to_string(i));
		win.wait_for_button();
	}
}