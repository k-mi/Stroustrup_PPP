#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_7");
	Graph_lib::Polygon wall, roof, door, window1, window2, funnel;

	wall.add(Point(150, 190));
	wall.add(Point(490, 190));
	wall.add(Point(490, 430));
	wall.add(Point(150, 430));
	wall.set_fill_color(Color::blue);

	roof.add(Point(100, 190));
	roof.add(Point(540, 190));
	roof.add(Point(320, 50));
	roof.set_fill_color(Color::red);

	door.add(Point(370, 250));
	door.add(Point(470, 250));
	door.add(Point(470, 430));
	door.add(Point(370, 430));
	door.set_fill_color(Color::dark_red);

	window1.add(Point(170, 220));
	window1.add(Point(170, 290));
	window1.add(Point(240, 290));
	window1.add(Point(240, 220));
	window1.set_fill_color(Color::cyan);

	window2.add(Point(260, 220));
	window2.add(Point(260, 290));
	window2.add(Point(330, 290));
	window2.add(Point(330, 220));
	window2.set_fill_color(Color::cyan);

	funnel.add(Point(160, 30));
	funnel.add(Point(180, 30));
	funnel.add(Point(190, 190));
	funnel.add(Point(150, 190));
	funnel.set_fill_color(Color::dark_red);

	win.attach(funnel);
	win.attach(wall);
	win.attach(roof);
	win.attach(door);
	win.attach(window1);
	win.attach(window2);
	
	win.wait_for_button();
}