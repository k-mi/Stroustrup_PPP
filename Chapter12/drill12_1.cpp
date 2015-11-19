#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(0, 0), 600, 400, "My window");
	win.wait_for_button();
}