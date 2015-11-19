﻿#include "GUI.h"
#include "Graph.h"

namespace Graph_lib{
	class Lines_window : public Window{
	public:
		Lines_window(Point xy, int w, int h, const string& title);
		Open_polyline lines;

	private:
		Button next_button;	// (next_x, next_y)をlinesに追加する
		Button quit_button;
		In_box next_x;
		In_box next_y;
		Out_box xy_out;

		static void cb_next(Address, Address);	// next_buttonのコールバック
		void next();
		static void cb_quit(Address, Address);	// quit_buttonのコールバック
		void quit();
	};

	Lines_window::Lines_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		next_button(Point(x_max() - 150, 0), 70, 20, "Next point", cb_next),
		quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quit),
		next_x(Point(x_max() - 310, 0), 50, 20, "next x:"),
		next_y(Point(x_max() - 210, 0), 50, 20, "next y:"),
		xy_out(Point(100, 0), 100, 20, "(x,y):")
	{
		attach(next_button);
		attach(quit_button);
		attach(next_x);
		attach(next_y);
		attach(xy_out);
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