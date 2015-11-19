#include "Graph.h"
#include "GUI.h"

namespace Graph_lib{
	double square(double x){ return x * x; }

	class Graph_window : public Graph_lib::Window{
	public:
		Graph_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			menu_button(Point(x_max() - 70, 0), 70, 20, "function", cb_menu),
			function_menu(Point(x_max() - 70, 0), 70, 20, Menu::vertical, "menu"),
			fct(0), scale(30), r_min(-10), r_max(11),
			ax(Axis::x, Point(20, y_max() / 2), x_max() - 40, (x_max() - 40) / scale),
			ay(Axis::y, Point(x_max() / 2, y_max() - 20), y_max() - 40, (y_max() - 40) / scale)
		{	
			attach(menu_button);
			attach(ax);
			attach(ay);

			function_menu.attach(new Button(Point(x_max() - 150, 0), 70, 20, "sin", cb_sin));
			function_menu.attach(new Button(Point(x_max() - 150, 20), 70, 20, "cos", cb_cos));
			function_menu.attach(new Button(Point(x_max() - 150, 40), 70, 20, "tan", cb_tan));
			function_menu.attach(new Button(Point(x_max() - 150, 60), 70, 20, "x^2", cb_square));
			attach(function_menu);
			function_menu.hide();
		}

		~Graph_window(){
			if(fct != 0){
				detach(*fct);
				delete fct;
			}
		}

	private:
		Button menu_button;
		Menu function_menu;
		Function* fct;

		double scale;	// 倍率
		int r_min;		// 範囲[r_min:r_max)
		int r_max;
		Axis ax;
		Axis ay;

		static void cb_menu(Address, Address pw) { reference_to<Graph_window>(pw).menu(); }
		void menu() { menu_button.hide(); function_menu.show(); }

		// 関数をグラフ化
		void view_function(double(*f)(double)){
			function_menu.hide();

			if(fct != 0){
				detach(*fct);
				delete fct;
			}

			fct = new Function(f, r_min, r_max, Point(x_max() / 2, y_max() / 2), 400, scale, scale);
			attach(*fct);
			menu_button.show();
		}

		static void cb_sin(Address, Address pw) { reference_to<Graph_window>(pw).f_sin(); }
		static void cb_cos(Address, Address pw) { reference_to<Graph_window>(pw).f_cos(); }
		static void cb_tan(Address, Address pw) { reference_to<Graph_window>(pw).f_tan(); }
		static void cb_square(Address, Address pw) { reference_to<Graph_window>(pw).f_square(); }

		void f_sin() { view_function(sin); }
		void f_cos() { view_function(cos); }
		void f_tan() { view_function(tan); }
		void f_square() { view_function(square); }
	};
}


int main(){
	using namespace Graph_lib;

	Graph_window win(Point(100, 100), 600, 400, "Graph");
	gui_main();
}