#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win14(Point(100, 100), 600, 400, "marked polyline");
													
	Marked_polyline mpl("1234");
	mpl.add(Point(100, 100));
	mpl.add(Point(150, 200));
	mpl.add(Point(250, 250));
	mpl.add(Point(300, 200));

	win14.attach(mpl);
	win14.wait_for_button();		// 表示！
}