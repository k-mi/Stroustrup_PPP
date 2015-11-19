#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 1000, 800, "drill13");

	win.wait_for_button();
}