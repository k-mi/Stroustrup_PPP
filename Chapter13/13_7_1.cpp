#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win7(Point(100, 100), 600, 400, "Closed polyline");

	Closed_polyline cpl;
	cpl.add(Point(100, 100));
	cpl.add(Point(150, 200));
	cpl.add(Point(250, 250));
	cpl.add(Point(300, 200));

	win7.attach(cpl);
	win7.wait_for_button();		// 表示！
}