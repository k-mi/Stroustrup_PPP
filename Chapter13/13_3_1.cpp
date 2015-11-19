// 2つのラインの描画

#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win2(Point(100, 100), 600, 400, "lines: +");

	Lines x;

	x.add(Point(100, 100), Point(200, 100));	// 1つ目のライン: 水平
	x.add(Point(150, 50), Point(150, 150));		// 2つ目のライン: 垂直

	win2.attach(x);
	win2.wait_for_button();		// 表示！
}