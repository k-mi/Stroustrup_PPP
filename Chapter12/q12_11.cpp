#include <cmath>
#include "Simple_window.h"
#include "Graph.h"

#define M_PI (acos(-1))

int main(){
	Simple_window win(Point(100, 100), 640, 480, "q12_11");
	Graph_lib::Polygon p3, p4, p5, p6, p7, p8;
		
	const int sx = 150, sy = 50;	// 原点
	int length = 200;				// 一辺の長さ

	int angle;						// 角の数
	int x, y;						// ポリゴンに設定する点
	double rad;						// 外角
	double offset = 0;				// 回転

	angle = 3;
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	for(int i = 1; i <= angle; ++i)
		p3.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));	// 数学とはy座標が逆なのでマイナスに設定

	angle = 4;
	offset += ((M_PI - 2 * M_PI / angle) - (M_PI - rad)) / 2;	// angle角形の内角と(angle-1)角形の内角の差/2を求める
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	length = 194;
	for(int i = 1; i <= angle; ++i)
		p4.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));

	angle = 5;
	offset += ((M_PI - 2 * M_PI / angle) - (M_PI - rad)) / 2;
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	length = 180;
	for(int i = 1; i <= angle; ++i)
		p5.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));

	angle = 6;
	offset += ((M_PI - 2 * M_PI / angle) - (M_PI - rad)) / 2;
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	length = 164;
	for(int i = 1; i <= angle; ++i)
		p6.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));

	angle = 7;
	offset += ((M_PI - 2 * M_PI / angle) - (M_PI - rad)) / 2;
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	length = 151;
	for(int i = 1; i <= angle; ++i)
		p7.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));

	angle = 8;
	offset += ((M_PI - 2 * M_PI / angle) - (M_PI - rad)) / 2;
	rad = 2 * M_PI / angle;
	x = sx, y = sy;
	length = 138;
	for(int i = 1; i <= angle; ++i)
		p8.add(Point(x += length * sin(rad * i + offset), y -= length * cos(rad * i + offset)));

	win.attach(p3);
	win.attach(p4);
	win.attach(p5);
	win.attach(p6);
	win.attach(p7);
	win.attach(p8);
	win.wait_for_button();
}