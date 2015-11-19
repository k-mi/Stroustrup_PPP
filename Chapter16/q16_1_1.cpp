#include "Graph.h"
#include "GUI.h"
#include "Simple_window.h"

namespace Graph_lib{
	// nextとquitの2つボタンを持つウインドウ
	class My_window : public Simple_window{
	public:
		My_window(Point xy, int w, int h, const string& title) 
			: Simple_window(xy, w, h, title),
			quit_button(Point(x_max() - 70, 20), 70, 20, "Quit", cb_quit)
		{
			attach(quit_button);
		}

	private:
		Button quit_button;

		static void cb_quit(Address, Address pw){ reference_to<My_window>(pw).quit(); }	// コールバック関数
		void quit(){ hide(); exit(EXIT_SUCCESS); }
	};
}

int main(){
	My_window win(Point(100, 100), 600, 400, "q16_1");

	win.wait_for_button();
	win.wait_for_button();
	win.wait_for_button();
	win.wait_for_button();
}