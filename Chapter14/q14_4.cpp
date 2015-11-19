#include "Graph.h"

namespace Graph_lib{
	// 移動できないCircleクラス
	class Immobile_Circle :public Circle{
	public:
		Immobile_Circle(Point p, int rr) : Circle(p, rr) { }

	private:
		void move(int dx, int dy) { }	// move関数をオーバーロードしてprivateに設定
	};
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Immobile_Circle");

	Immobile_Circle ic(Point(300, 200), 200);
	
	win.attach(ic);
	win.wait_for_button();
}