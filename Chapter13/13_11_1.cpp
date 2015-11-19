#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win11(Point(100, 100), 600, 400, "Closed polyline with text");

	Closed_polyline cpl;
	cpl.add(Point(100, 100));
	cpl.add(Point(150, 200));
	cpl.add(Point(250, 250));
	cpl.add(Point(300, 200));
	cpl.add(Point(100, 250));

	Text t(Point(200, 200), "A closed polyline that isn't a polygon");
	t.set_color(Color::blue);

	win11.attach(cpl);
	win11.attach(t);
	win11.wait_for_button();		// 表示！
}