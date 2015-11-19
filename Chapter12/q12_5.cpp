#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win(Point(0, 0), x_max(), y_max(), "q12_5");
	
	const int w = 20;	// フレーム幅
	Graph_lib::Rectangle frame(Point(0, 0), x_max() / 4 * 3 + w * 2, y_max() / 3 * 2 + w * 2);
	frame.move((x_max() - frame.width())/ 2, (y_max() - frame.height()) / 2);	// ウインドウ中央に配置
	frame.set_fill_color(Color::red);
	
	Graph_lib::Rectangle rect(Point(0, 0), x_max() / 4 * 3, y_max() / 3 * 2);
	rect.move((x_max() - rect.width()) / 2, (y_max() - rect.height()) / 2);		// ウインドウ中央に配置
	rect.set_fill_color(Color::white);

	win.attach(frame);
	win.attach(rect);
	win.wait_for_button();
}