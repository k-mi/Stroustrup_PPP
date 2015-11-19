#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win3(Point(100, 100), 600, 400, "grid");

	int x_size = win3.x_max();	// ウインドウのサイズを取得する
	int y_size = win3.y_max();
	int x_grid = 80;
	int y_grid = 40;

	Lines grid;
	for(int x = x_grid; x < x_size; x += x_grid)
		grid.add(Point(x, 0), Point(x, y_size));
	for(int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point(0, y), Point(x_size, y));

	win3.attach(grid);
	win3.wait_for_button();		// 表示！
}