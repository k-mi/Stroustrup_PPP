#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win6(Point(100, 100), 600, 400, "Open polyline");

	Open_polyline opl;
	opl.add(Point(100, 100));
	opl.add(Point(150, 200));
	opl.add(Point(250, 250));
	opl.add(Point(300, 200));

	win6.attach(opl);
	win6.wait_for_button();		// 表示！
}