#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_3");

	Point p(200, 150);
	Text t1(p, "M");
	Text t2(p, "   .    .");
	Text t3(p, "     K");
	t1.set_font(Font::helvetica_bold);
	t2.set_font(Font::helvetica_bold);
	t3.set_font(Font::helvetica_bold);
	t1.set_color(Color::dark_cyan);
	t3.set_color(Color::blue);

	win.attach(t1);
	win.attach(t2);
	win.attach(t3);

	win.wait_for_button();

	return 0;
}