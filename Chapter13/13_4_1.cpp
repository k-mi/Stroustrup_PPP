#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win4(Point(100, 100), 600, 400, "red grid");

	int x_size = win4.x_max();	// ウインドウのサイズを取得する
	int y_size = win4.y_max();
	int x_grid = 80;
	int y_grid = 40;

	Lines grid;
	for(int x = x_grid; x < x_size; x += x_grid)
		grid.add(Point(x, 0), Point(x, y_size));
	for(int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point(0, y), Point(x_size, y));

	grid.set_color(Color::red);

	win4.attach(grid);
	win4.wait_for_button();		// 表示！
}