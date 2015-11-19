#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_8");

	Circle c1(Point(100, 100), 100);
	c1.set_style(Line_style(Line_style::solid, 20));
	c1.set_color(Color::cyan);

	Circle c2(Point(320, 100), 100);
	c2.set_style(Line_style(Line_style::solid, 20));
	c2.set_color(Color::black);

	Circle c3(Point(540, 100), 100);
	c3.set_style(Line_style(Line_style::solid, 20));
	c3.set_color(Color::red);

	Circle c4(Point(200, 200), 100);
	c4.set_style(Line_style(Line_style::solid, 20));
	c4.set_color(Color::yellow);

	Circle c5(Point(440, 200), 100);
	c5.set_style(Line_style(Line_style::solid, 20));
	c5.set_color(Color::green);

	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(c4);
	win.attach(c5);
	win.wait_for_button();
}