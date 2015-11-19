#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_10");

	Image pic(Point(0, 0), "../olympic.jpg");

	win.attach(pic);
	win.wait_for_button();
}