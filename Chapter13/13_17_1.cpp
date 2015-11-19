#include "Simple_window.h"
#include "Graph.h"

int main(){
	Simple_window win17(Point(100, 100), 600, 400, "Image");
	
	Image rita(Point(0, 0), "../rita.jpg");
	Image path(Point(0, 0), "../rita_path.gif");
	path.set_mask(Point(50, 250), 600, 400);	// 予想上陸地点を選択する

	win17.attach(path);
	win17.attach(rita);
	win17.wait_for_button();		// 表示！
}