#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_2");

	Graph_lib::Rectangle rect(Point(100, 100), 100, 30);

	Text t(Point(100, 120), "Howdy!");

	win.attach(rect);
	win.attach(t);

	win.wait_for_button();

	return 0;
}