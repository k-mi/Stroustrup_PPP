#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win9(Point(100, 100), 600, 400, "rectangles");

	Graph_lib::Rectangle rect00(Point(150, 100), 200, 100);
	Graph_lib::Rectangle rect11(Point(50, 50), Point(250, 150));
	Graph_lib::Rectangle rect12(Point(50, 150), Point(250, 250));	// rect11のすぐ下
	Graph_lib::Rectangle rect21(Point(250, 50), 200, 100);			// rext11のすぐ右
	Graph_lib::Rectangle rect22(Point(250, 150), 200, 100);			// rext21のすぐ下

	rect00.set_fill_color(Color::yellow);
	rect11.set_fill_color(Color::blue);
	rect12.set_fill_color(Color::red);
	rect21.set_fill_color(Color::green);

	win9.attach(rect00);
	win9.attach(rect11);
	win9.attach(rect12);
	win9.attach(rect21);
	win9.attach(rect22);
	win9.wait_for_button();		// 表示！

	rect11.move(400, 0);
	rect11.set_fill_color(Color::white);
	win9.set_label("rectangles 2");
	win9.wait_for_button();

	win9.put_on_top(rect00);
	win9.set_label("rectangles 3");
	win9.wait_for_button();

	rect00.set_color(Color::invisible);
	rect11.set_color(Color::invisible);
	rect12.set_color(Color::invisible);
	rect21.set_color(Color::invisible);
	rect22.set_color(Color::invisible);
	win9.set_label("rectangles 4");
	win9.wait_for_button();
}