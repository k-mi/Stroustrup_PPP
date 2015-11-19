#include <cmath>
#include "GUI.h"
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Regular_polygon : public Polygon{
	public:
		Regular_polygon(Point pp, int rr, int nn) : p(pp)
		{
			r = rr;
			if(r <= 0) error("Bad polygon: non-positive radius length");
			n = nn;
			if(n < 3) error("Bad polygon: less than 3 sides");

			double angle = 0;
			for(int i = 0; i < n; ++i) {
				add(Point(p.x + r * cos(angle), p.y - r * sin(angle)));
				angle += 2 * M_PI / n;
			}
		}

		void draw_lines() const { Polygon::draw_lines(); }

		Point center() { return p; }
		int radius() { return r; }

	private:
		Point p;	// 中心座標
		int r;		// 中心から角までの距離
		int n;		// 辺の数
	};

	// nextとquitの2つのボタンを持つウインドウ
	class My_window : public Graph_lib::Window{
	public:
		My_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			button_pressed(false),
			next_button(Point(x_max() - 150, 0), 70, 20, "next", cb_next),
			quit_button(Point(x_max() - 70, 0), 70, 20, "quit", cb_quit)
		{
			attach(next_button);
			attach(quit_button);
		}

		void wait_for_button(){
			while(!button_pressed)
				Fl::wait();			// 待機
			button_pressed = false;
			Fl::redraw();			// 再描画
		}

	protected:
		bool button_pressed;

	private:
		Button next_button;
		Button quit_button;

		static void cb_next(Address, Address pw) { reference_to<My_window>(pw).next(); }
		static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); }

		void next() { button_pressed = true; }
		void quit() { hide(); exit(EXIT_SUCCESS); }		// 終了
	};

	class Shape_window : public My_window{
	public:
		Shape_window(Point xy, int w, int h, const string& title)
			: My_window(xy, w, h, title),
			inbox_x(Point(20, 0), 70, 20, "X:"),
			inbox_y(Point(120, 0), 70, 20, "Y:"),
			menu(Point(x_max() - 230, 0), 70, 20, "kind", cb_menu),
			kind(Point(x_max() - 230, 0), 70, 20, Menu::vertical, "shape kind")
		{
			attach(inbox_x);
			attach(inbox_y);
			attach(menu);

			kind.attach(new Button(Point(x_max() - 230, 0), 70, 20, "circle", cb_circle));
			kind.attach(new Button(Point(x_max() - 230, 20), 70, 20, "triangle", cb_triangle));
			kind.attach(new Button(Point(x_max() - 230, 40), 70, 20, "square", cb_square));
			kind.attach(new Button(Point(x_max() - 230, 60), 70, 20, "hexagon", cb_hexagon));
			attach(kind);
			kind.hide();
		}

		void wait_for_button(){
			while(!My_window::button_pressed)
				Fl::wait();		// 待機

			// 一番新しい図形を移動
			shapes[shapes.size() - 1].move(inbox_x.get_int() - x, inbox_y.get_int() - y);
			x = inbox_x.get_int();
			y = inbox_y.get_int();

			My_window::button_pressed = false;
			Fl::redraw();		// 再描画
		}
		
	private:
		In_box inbox_x;
		In_box inbox_y;
		Button menu;
		Menu kind;
		Vector_ref<Shape> shapes;

		static void cb_menu(Address, Address pw){ reference_to<Shape_window>(pw).menu_push(); }
		static void cb_circle(Address, Address pw){ reference_to<Shape_window>(pw).circle_push(); }
		static void cb_triangle(Address, Address pw){ reference_to<Shape_window>(pw).triangle_push(); }
		static void cb_square(Address, Address pw){ reference_to<Shape_window>(pw).square_push(); }
		static void cb_hexagon(Address, Address pw){ reference_to<Shape_window>(pw).hexagon_push(); }

		void menu_push(){ menu.hide(); kind.show(); }

		const int radius = 50;	// 図形の中心から角（周）までの距離
		int x, y;				// 取得した座標

		void circle_push(){
			kind.hide();
			x = inbox_x.get_int();
			y = inbox_y.get_int();
			shapes.push_back(new Circle(Point(x, y), radius));
			attach(shapes[shapes.size() - 1]);
			menu.show();
		}

		void triangle_push(){
			kind.hide();
			x = inbox_x.get_int();
			y = inbox_y.get_int();
			shapes.push_back(new Regular_polygon(Point(x, y), radius, 3));
			attach(shapes[shapes.size() - 1]);
			menu.show();
		}

		void square_push(){
			kind.hide();
			x = inbox_x.get_int();
			y = inbox_y.get_int();
			shapes.push_back(new Regular_polygon(Point(x, y), radius, 4));
			attach(shapes[shapes.size() - 1]);
			menu.show();
		}

		void hexagon_push(){
			kind.hide();
			x = inbox_x.get_int();
			y = inbox_y.get_int();
			shapes.push_back(new Regular_polygon(Point(x, y), radius, 6));
			attach(shapes[shapes.size() - 1]);
			menu.show();
		}
	};
}

int main(){
	using namespace Graph_lib;

	Shape_window win(Point(100, 100), 600, 400, "Shape window");

	while(true)
		win.wait_for_button();
}