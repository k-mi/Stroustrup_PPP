#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win13(Point(100, 100), 600, 400, "ellipse");

	Graph_lib::Ellipse e1(Point(200, 200), 50, 50);
	Graph_lib::Ellipse e2(Point(200, 200), 100, 50);
	Graph_lib::Ellipse e3(Point(200, 200), 100, 150);

	win13.attach(e1);
	win13.attach(e2);
	win13.attach(e3);
	win13.wait_for_button();		// 表示！
}