#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win15(Point(100, 100), 600, 400, "marks");

	Marks pp("x");
	pp.add(Point(100, 100));
	pp.add(Point(150, 200));
	pp.add(Point(250, 250));
	pp.add(Point(300, 200));

	win15.attach(pp);
	win15.wait_for_button();		// 表示！
}