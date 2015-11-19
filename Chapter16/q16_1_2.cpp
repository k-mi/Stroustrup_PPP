#include "GUI.h"
#include "Graph.h"

namespace Graph_lib{
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

		void wait_for_button();

	private:
		bool button_pressed;

		Button next_button;
		Button quit_button;

		static void cb_next(Address, Address pw) { reference_to<My_window>(pw).next(); }
		static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); } 

		void next() { button_pressed = true; }
		void quit() { hide(); exit(EXIT_SUCCESS); }
	};

	void My_window::wait_for_button(){
		while(!button_pressed) 
			Fl::wait();			// 待機
		button_pressed = false;
		Fl::redraw();			// 再描画
	}
}

int main(){
	using namespace Graph_lib;

	My_window win(Point(100, 100), 600, 400, "Simple_window");
	Circle c(Point(300, 200), 150);

	win.attach(c);
	win.wait_for_button();

	c.set_fill_color(Color::magenta);
	win.wait_for_button();
}