#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "RGB color chart");
	Vector_ref<Graph_lib::Rectangle> vr;
	
	int x = 0, y = 0;		// 座標
	const int a = 15;		// 正方形の一辺
	const int step = 51;	// Webセーフカラー（ = 0x33 ）

	for(int r = 0; r <= 255; r += step, y += a, x = 0){
		for(int g = 0; g <= 255; g += step){
			for(int b = 0; b <= 255; b += step, x += a){
				vr.push_back(new Graph_lib::Rectangle(Point(x, y), a, a));
				vr[vr.size() - 1].set_fill_color(Color(r * pow(2, 24) + g * pow(2, 16) + b * pow(2, 8)));
				win.attach(vr[vr.size() - 1]);						
			}
		}
	}

	win.wait_for_button();
}