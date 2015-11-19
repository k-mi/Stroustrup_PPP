#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win8(Point(100, 100), 600, 400, "Polygon");

	Graph_lib::Polygon poly;
	poly.add(Point(100, 100));
	poly.add(Point(150, 200));
	poly.add(Point(250, 250));
	poly.add(Point(300, 200));

	win8.attach(poly);
	win8.wait_for_button();		// 表示！
}