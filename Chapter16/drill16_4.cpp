#include "GUI.h"
#include "Graph.h"

namespace Graph_lib{
	class Lines_window : public Window{
	public:
		Lines_window(Point xy, int w, int h, const string& title);

	private:
		// データ:
		Open_polyline lines;

		// widgets:
		Button next_button;	// (next_x, next_y)をlinesに追加する
		Button quit_button;	// プログラムを終了する
		In_box next_x;
		In_box next_y;
		Out_box xy_out;
		Menu color_menu;
		Button color_menu_button;
		Menu style_menu;
		Button style_menu_button;

		void change_color(Color c) { lines.set_color(c); }
		void change_style(Line_style s) { lines.set_style(s); }
		void hide_menu() { color_menu.hide(); style_menu.hide(); color_menu_button.show(); style_menu_button.show(); }

		// コールバックによって呼び出されるアクション
		void red_pressed() { change_color(Color::red); hide_menu(); }
		void blue_pressed() { change_color(Color::blue); hide_menu(); }
		void black_pressed() { change_color(Color::black); hide_menu(); }
		void color_menu_pressed() { hide_menu(); color_menu_button.hide(); color_menu.show(); }

		void solid_pressed() { change_style(Line_style::solid); hide_menu(); }
		void dash_pressed() { change_style(Line_style::dash); hide_menu(); }
		void dashdot_pressed() { change_style(Line_style::dashdot); hide_menu(); }
		void dashdotdot_pressed() { change_style(Line_style::dashdotdot); hide_menu(); }
		void dot_pressed() { change_style(Line_style::dot); hide_menu(); }
		void style_menu_pressed() { hide_menu(); style_menu_button.hide(); style_menu.show(); }

		void next();
		void quit();

		// コールバック関数
		static void cb_red(Address, Address);
		static void cb_blue(Address, Address);
		static void cb_black(Address, Address);
		static void cb_color_menu(Address, Address);

		static void cb_solid(Address, Address);
		static void cb_dash(Address, Address);
		static void cb_dashdot(Address, Address);
		static void cb_dashdotdot(Address, Address);
		static void cb_dot(Address, Address);
		static void cb_style_menu(Address, Address);

		static void cb_next(Address, Address);
		static void cb_quit(Address, Address);
	};

	Lines_window::Lines_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		next_button(Point(x_max() - 150, 0), 70, 20, "Next point", cb_next),
		quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quit),
		next_x(Point(x_max() - 310, 0), 50, 20, "next x:"),
		next_y(Point(x_max() - 210, 0), 50, 20, "next y:"),
		xy_out(Point(100, 0), 100, 20, "(x,y):"),
		color_menu(Point(x_max() - 70, 40), 70, 20, Menu::vertical, "color"),
		color_menu_button(Point(x_max() - 70, 40), 70, 20, "color", cb_color_menu),
		style_menu(Point(x_max() - 150, 40), 70, 20, Menu::vertical, "style"),
		style_menu_button(Point(x_max() - 150, 40), 70, 20, "style", cb_style_menu)
	{
		attach(next_button);
		attach(quit_button);
		attach(next_x);
		attach(next_y);
		attach(xy_out);
		xy_out.put("no print");

		color_menu.attach(new Button(Point(0, 0), 0, 0, "red", cb_red));
		color_menu.attach(new Button(Point(0, 0), 0, 0, "blue", cb_blue));
		color_menu.attach(new Button(Point(0, 0), 0, 0, "black", cb_black));
		attach(color_menu);
		style_menu.attach(new Button(Point(0, 0), 0, 0, "solid", cb_solid));
		style_menu.attach(new Button(Point(0, 0), 0, 0, "dash", cb_dash));
		style_menu.attach(new Button(Point(0, 0), 0, 0, "dashdot", cb_dashdot));
		style_menu.attach(new Button(Point(0, 0), 0, 0, "dashdotdot", cb_dashdotdot));
		style_menu.attach(new Button(Point(0, 0), 0, 0, "dot", cb_dot));
		attach(style_menu);

		color_menu.hide();
		style_menu.hide();

		attach(color_menu_button); 
		attach(style_menu_button);
		attach(lines);
	}

	void Lines_window::cb_quit(Address, Address pw){
		reference_to<Lines_window>(pw).quit();
	}

	void Lines_window::quit(){
		hide();	// ウインドウを削除するためのFLTKイディオム
	}

	void Lines_window::cb_next(Address, Address pw){
		reference_to<Lines_window>(pw).next();
	}

	void Lines_window::next(){
		int x = next_x.get_int();
		int y = next_y.get_int();

		lines.add(Point(x, y));

		// 現在の読み取り位置を更新する
		ostringstream ss;
		ss << '(' << x << ',' << y << ')';
		xy_out.put(ss.str());

		redraw();
	}

	void Lines_window::cb_red(Address, Address pw){	reference_to<Lines_window>(pw).red_pressed(); }
	void Lines_window::cb_blue(Address, Address pw){ reference_to<Lines_window>(pw).blue_pressed();	}
	void Lines_window::cb_black(Address, Address pw){ reference_to<Lines_window>(pw).black_pressed(); }
	void Lines_window::cb_color_menu(Address, Address pw){ reference_to<Lines_window>(pw).color_menu_pressed();	}

	void Lines_window::cb_solid(Address, Address pw){ reference_to<Lines_window>(pw).solid_pressed(); }
	void Lines_window::cb_dash(Address, Address pw){ reference_to<Lines_window>(pw).dash_pressed(); }
	void Lines_window::cb_dashdot(Address, Address pw){ reference_to<Lines_window>(pw).dashdot_pressed(); }
	void Lines_window::cb_dashdotdot(Address, Address pw){ reference_to<Lines_window>(pw).dashdotdot_pressed(); }
	void Lines_window::cb_dot(Address, Address pw){ reference_to<Lines_window>(pw).dot_pressed(); }
	void Lines_window::cb_style_menu(Address, Address pw){ reference_to<Lines_window>(pw).style_menu_pressed(); }
}

int main(){
	using namespace Graph_lib;

	try{
		Lines_window win(Point(100, 100), 600, 400, "lines");
		return gui_main();
	}
	catch(exception& e){
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch(...){
		cerr << "Some exception\n";
		return 2;
	}
}