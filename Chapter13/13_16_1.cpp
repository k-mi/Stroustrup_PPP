#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win16(Point(100, 100), 600, 400, "Mark");
	Circle c1(Point(100, 200), 50);
	Circle c2(Point(150, 200), 100);
	Circle c3(Point(200, 200), 150);

	Mark m1(Point(100, 200), 'x');
	Mark m2(Point(150, 200), 'y');
	Mark m3(Point(200, 200), 'z');
	
	c1.set_color(Color::blue);
	c2.set_color(Color::red);
	c3.set_color(Color::green);

	win16.attach(c1);
	win16.attach(c2);
	win16.attach(c3);
	win16.attach(m1);
	win16.attach(m2);
	win16.attach(m3);
	win16.wait_for_button();		// 表示！
}