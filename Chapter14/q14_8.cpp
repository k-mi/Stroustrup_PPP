#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Octagon : public Polygon{
	public:
		Octagon(Point pp, int rr) : p(pp)
		{
			r = rr;
			if(r <= 0) error("Bad octagon: non-positive radius length");

			const int n = 8;	// 八角形
			double angle = 0;
			for(int i = 0; i < n; ++i) {
				Polygon::add(Point(p.x + r * cos(angle), p.y - r * sin(angle)));
				angle += 2 * M_PI / n;
			}
		}
		void draw_lines() const { Polygon::draw_lines(); }

		Point center() { return p; }
		int radius() { return r; }

	protected:
		// クラス外からの使用を禁止
		void add(Point p1, Point p2) {}
		void move(int dx, int dy) {}

	private:
		Point p;	// 中心座標
		int r;		// 中心から角までの距離
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Ocatagon");

	// Octagonクラスのテスト
	Octagon oct(Point(300, 200), 150);

	// パラメータを表示
	cout << "center: " << oct.center().x << ", " << oct.center().y << endl;
	cout << "radius: " << oct.radius() << endl;
	for(int i = 0; i < oct.number_of_points(); ++i)
		cout << "point" << i << ": " << oct.point(i).x << ", " << oct.point(i).y << endl;

	win.attach(oct);
	win.wait_for_button();

	oct.set_color(Color::dark_blue);				// 線の色を変更
	oct.set_style(Line_style(Line_style::dot, 5));	// 線の種類を変更
	win.wait_for_button();

	oct.set_fill_color(Color::dark_cyan);			// 塗りつぶし色を変更
	win.wait_for_button();

	//oct.move(50, 0);								// 使用できないメンバ関数
	//oct.add(Point(20, 20));						
}