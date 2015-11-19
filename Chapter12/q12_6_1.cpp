#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(0, 0), 640, 480, "q12_6_1");

	const int add = 100;	// 加算値
	Graph_lib::Rectangle rect(Point(0, 0), win.x_max() + add, win.y_max() + add);
	rect.set_fill_color(Color::dark_blue);

	win.attach(rect);
	win.wait_for_button();
}