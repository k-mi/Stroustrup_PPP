#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_4");
	
	const int size = 3;	// 表のサイズ
	const int wh = 150;	// 1つの正方形の一辺

	int i = 0;
	Graph_lib::Rectangle rect1(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect2(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect3(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect4(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect5(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect6(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect7(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect8(Point(i % size * wh, i / size * wh), wh, wh);
	i++;
	Graph_lib::Rectangle rect9(Point(i % size * wh, i / size * wh), wh, wh);

	rect1.set_fill_color(Color::white);
	rect3.set_fill_color(Color::white);
	rect5.set_fill_color(Color::white);
	rect7.set_fill_color(Color::white);
	rect9.set_fill_color(Color::white);
	rect2.set_fill_color(Color::black);
	rect4.set_fill_color(Color::black);
	rect6.set_fill_color(Color::black);
	rect8.set_fill_color(Color::black);

	win.attach(rect1);
	win.attach(rect2);
	win.attach(rect3);
	win.attach(rect4);
	win.attach(rect5);
	win.attach(rect6);
	win.attach(rect7);
	win.attach(rect8);
	win.attach(rect9);
	
	win.wait_for_button();

	return 0;
}