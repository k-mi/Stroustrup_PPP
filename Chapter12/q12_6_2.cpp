#include "Simple_window.h"
#include "Graph.h"

int main(){
	const int add = 500;	// 加算値
	Simple_window win(Point(0, 0), x_max() + add, y_max() + add, "q12_6_2");

	win.wait_for_button();
}