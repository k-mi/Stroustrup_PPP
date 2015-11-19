#include "Simple_window.h"
#include "Graph.h"

int main(){
	const string pic_name = "dog";
	Simple_window win(Point(100, 100), 640, 480, pic_name);

	Image pic(Point(200, 200), "../image1.jpg");	// 128×128の画像
	Text t(Point(250, 340), pic_name);

	win.attach(pic);
	win.attach(t);
	win.wait_for_button();
}