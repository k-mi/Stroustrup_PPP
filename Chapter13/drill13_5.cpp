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

	Image i1(Point(300, 0), "../image1.jpg");
	Image i2(Point(600, 200), "../image1.jpg");
	Image i3(Point(100, 500), "../image1.jpg");
	win.attach(i1);
	win.attach(i2);
	win.attach(i3);

	win.wait_for_button();

	for(int i = 0; i < max; i += interval)
	{
		for(int j = 0; j < max; j += interval){
			Image i4(Point(j, i), "../image2.jpg");
			win.attach(i4);
			win.wait_for_button();
		}
	}

}