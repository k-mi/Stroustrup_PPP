#include "Graph.h"
#include "Simple_window.h"
using namespace Graph_lib;

// Graph.hおよびGraph.cppにテキストベースの出力フォーマットのためのコードを追加
// OBJ_TEXTが定義されているときのみ、派生クラスのコンストラクタ内で実行される

int main() {
	Simple_window win(Point(100, 100), 600, 400, "GUI textbase output");

	Vector_ref<Shape> vr;
	vr.push_back(new Line(Point(250, 250), Point(350, 350)));
	vr.push_back(new Graph_lib::Rectangle(Point(100, 300), 50, 50));
	vr.push_back(new Graph_lib::Rectangle(Point(250, 250), Point(350, 350)));
	vr.push_back(new Circle(Point(100, 100), 50));
	vr.push_back(new Graph_lib::Ellipse(Point(100, 100), 20, 40));
	vr.push_back(new Text(Point(350, 350), "test"));
	
	for(int i = 0; i < vr.size(); ++i)
		win.attach(vr[i]);

	win.wait_for_button();
}