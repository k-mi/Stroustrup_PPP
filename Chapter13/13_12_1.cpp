#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win12(Point(100, 100), 600, 400, "Circle");

	Circle c1(Point(100, 200), 50);
	Circle c2(Point(150, 200), 100);
	Circle c3(Point(200, 200), 150);

	win12.attach(c1);
	win12.attach(c2);
	win12.attach(c3);
	win12.wait_for_button();		// 表示！
}