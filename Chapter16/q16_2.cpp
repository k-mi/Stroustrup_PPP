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

	class Checker_window : public My_window{
	public:
		Checker_window(Point xy, int w, int h, const string& title)
			: My_window(xy, w, h, title), outbox(Point(0, 0), x_max() - 160, 20, "(x, y)")
		{
			attach(outbox);
			
			const int column = 4;	// 列数
			const int row = 4;		// 行数

			for(int i = 0; i < column * row; ++i){
				checker.push_back(new Button(Point(x_max() / column * (i % column), (y_max() - 20) / row * (i / row) + 20),
					x_max() / column, (y_max() - 20) / row, to_string(i), cb_checker));
				attach(checker[i]);
			}
		}

	private:
		Out_box outbox;
		Vector_ref<Button> checker;

		static void cb_checker(Address a, Address pw) {
			Fl_Button &trigger = reference_to<Fl_Button>(a);	// コールバックの引き金となったGUIエンティティ
			reference_to<Checker_window>(pw).pressed(trigger.x(), trigger.y()); 
		}
		
		void pressed(int x, int y) {
			ostringstream oss;
			oss << '(' << x << ", " << y << ")";
			outbox.put(oss.str()); 
		}
	};
}

int main(){
	using namespace Graph_lib;

	Checker_window win(Point(100, 100), 600, 400, "Checker window");
	win.wait_for_button();
}