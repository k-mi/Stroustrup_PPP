#include <vector>
#include "Graph.h"
using namespace std;
using namespace Graph_lib;

// 設計に問題のあるインターフェース
void poor(Shape* p, int sz) {
	for(int i = 0; i < sz; ++i) p[i].draw();
}

// 非常によくないコード
void f(Shape* q, vector<Circle>& s0) {
	Graph_lib::Polygon s1[10];
	//Shape s2[10];				// Shapeにデフォルトコンストラクタは存在しない

	// 初期化
	Shape* p1 = new Graph_lib::Rectangle(Point(0, 0), Point(10, 20));

	//poor(&s0[0], s0.size());	// #1 エラー 要素型がShapeではない
	//poor(s1, 10);				// #2 エラー 要素型がShapeではない
	//poor(s2, 20);				// #3 エラー（s2をコメントアウト）
	poor(p1, 1);				// #4
	delete p1;
	p1 = 0;
	//poor(p1, 1);				// #5 エラー p1はヌルポインタ
	//poor(q, max);				// #6 エラー maxが定義されていない
}

int main() {
	vector<Circle> vc;
	Circle* c = new Circle(Point(100, 100), 20);

	f(c, vc);

	delete c;
}