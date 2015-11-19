#include "Simple_window.h"	// ウインドウライブラリにアクセスする
#include "Graph.h"			// グラフィクスライブラリにアクセスする

int main(){
	using namespace Graph_lib;	// グラフィックス機能はGraph_libに含まれている

	Point t1(100, 100);			// ウインドウの左上隅を定義する

	Simple_window win(t1, 600, 400, "Canvas");	// 単純なウインドウを作成する

	Graph_lib::Polygon poly;	// 図形（ポリゴン）を作成する

	poly.add(Point(300, 200));	// ポイントを追加する
	poly.add(Point(350, 100));	// 2つ目のポイントを追加する
	poly.add(Point(400, 200));	// 3つ目のポイントを追加する

	poly.set_color(Color::red);	// ポリゴンのプロパティを調整する

	win.attach(poly);			// ポリゴンをウインドウに接続する

	win.wait_for_button();		// 表示エンジンに制御を渡す
}