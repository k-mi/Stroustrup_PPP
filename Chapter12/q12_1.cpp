#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_1");
	
	Graph_lib::Rectangle rect(Point(100, 100), 200, 100);
	rect.set_color(Color::red);

	Graph_lib::Polygon poly;
	poly.add(Point(300, 300));
	poly.add(Point(500, 300));
	poly.add(Point(500, 400));
	poly.add(Point(300, 400));
	poly.set_color(Color::blue);

	win.attach(rect);
	win.attach(poly);
	
	win.wait_for_button();

	return 0;
}