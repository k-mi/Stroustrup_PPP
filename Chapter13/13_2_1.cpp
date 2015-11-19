// 2つのラインの描画

#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win1(Point(100, 100), 600, 400, "two lines");

	Line horizontal(Point(100, 100), Point(200, 100));	// 水平線を作成する
	Line Vertical(Point(150, 50), Point(150, 150));		// 垂直線を作成する

	win1.attach(horizontal);	//2つのラインをウインドウに関連づける
	win1.attach(Vertical);

	win1.wait_for_button();		// 表示！
}