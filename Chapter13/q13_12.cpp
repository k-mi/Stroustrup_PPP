#include <cmath>
#include "Simple_window.h"
#include "Graph.h"

#define M_PI (acos(-1))

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Circle");

	Point center(300, 200);
	Circle c(center, 150);
	win.attach(c);

	for(double angle = 0; angle <= 2 * M_PI; angle += 2 * M_PI / 12){
		Point p(c.center().x + c.radius() * cos(angle), c.center().y - c.radius() * sin(angle));
		Mark fp(p, 'x');
		win.attach(fp);
		win.wait_for_button();
	}
}