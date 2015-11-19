﻿#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win5(Point(100, 100), 600, 400, "red dotted grid");

	int x_size = win5.x_max();	// ウインドウのサイズを取得する
	int y_size = win5.y_max();
	int x_grid = 80;
	int y_grid = 40;

	Lines grid;
	for(int x = x_grid; x < x_size; x += x_grid)
		grid.add(Point(x, 0), Point(x, y_size));
	for(int y = y_grid; y < y_size; y += y_grid)
		grid.add(Point(0, y), Point(x_size, y));

	grid.set_color(Color::red);
	grid.set_style(Line_style::dot);

	win5.attach(grid);
	win5.wait_for_button();		// 表示！
}