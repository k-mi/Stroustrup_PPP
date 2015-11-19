#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 1000, 800, "drill13");

	Lines grid;
	const int max = 800;
	const int interval = 100;

	for(int i = 0; i <= max; i += interval)
		grid.add(Point(0, i), Point(max, i));
	for(int i = 0; i <= max; i += interval)
		grid.add(Point(i, 0), Point(i, max));
	win.attach(grid);

	Vector_ref<Graph_lib::Rectangle> vr;
	for(int i = 0; i < max; i += interval){
		vr.push_back(new Graph_lib::Rectangle(Point(i, i), 100, 100));
		vr[vr.size() - 1].set_fill_color(Color::red);
		win.attach(vr[vr.size() - 1]);
	}

	win.wait_for_button();
}