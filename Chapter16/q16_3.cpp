#include "GUI.h"
#include "Graph.h"

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

	// 乱数ジェネレータ
	int rint(int low, int high){
		return low + rand() % (high - low);
	}

	class Random_window : public My_window{
	public:
		Random_window(Point xy, int w, int h, const string& title)
			: My_window(xy, w, h, title), 
			x(rint(0, x_max() - 100)),
			y(rint(20, y_max() - 100)),
			image_button(Point(x, y), 100, 100, "", cb_image), 
			image(Point(x, y), "../image1.jpg")
		{
			attach(image_button);
			attach(image);
		}

	private:
		int x;
		int y;
		Button image_button;
		Image image;

		static void cb_image(Address, Address pw){ reference_to<Random_window>(pw).push(); }

		void push() { 
			int tmp_x = rint(0, x_max()- 100);
			int tmp_y = rint(20, y_max() - 100);

			image_button.move(tmp_x - x, tmp_y - y);
			image.move(tmp_x - x, tmp_y - y);

			x = tmp_x;
			y = tmp_y;
		}
	};
}

int main(){
	using namespace Graph_lib;

	Random_window win(Point(100, 100), 600, 400, "Random image");
	win.wait_for_button();
}