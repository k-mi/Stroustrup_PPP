#include "GUI.h"
#include "Graph.h"
#include <FL/Fl_Button.H>

namespace Graph_lib{
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

	private:
		bool button_pressed;

		Button next_button;
		Button quit_button;

		static void cb_next(Address, Address pw) { reference_to<My_window>(pw).next(); }
		static void cb_quit(Address, Address pw) { reference_to<My_window>(pw).quit(); }

		void next() { button_pressed = true; }
		void quit() { hide(); exit(EXIT_SUCCESS); }		// 終了
	};

	class Flying_window : public My_window{
	public:
		Flying_window(Point xy, int w, int h, const string& title)
			: My_window(xy, w, h, title),
			start_button(Point(0, 0), 70, 20, "start", cb_start),
			stop_button(Point(80, 0), 70, 20, "stop", cb_stop),
			airplane(Point(0, (y_max() - 100)/ 2), "../airplane.jpg"),
			is_moving(false)
		{
			attach(start_button);
			attach(stop_button);
			attach(airplane);
		}

	private:
		Button start_button;
		Button stop_button;
		Image airplane;
		bool is_moving;

		static void cb_start(Address, Address pw) { reference_to<Flying_window>(pw).start(); }
		static void cb_stop(Address, Address pw) { reference_to<Flying_window>(pw).stop(); }

		const int dx = 1;	// x方向の移動量

		void start() {
			is_moving = true;

			while(is_moving){
				if(airplane.point(0).x + dx <= x_max())
					airplane.move(10, 0);
				else
					airplane.move(-x_max() - 100, 0);

				Fl::redraw();	// 描画
				Fl::wait();
				Sleep(50);		// 50ミリ秒待機
			}
		}

		void stop(){
			is_moving = false;
		}
	};
}

int main(){
	using namespace Graph_lib;

	Flying_window win(Point(100, 100), 600, 400, "Airplane");
	win.wait_for_button();
}