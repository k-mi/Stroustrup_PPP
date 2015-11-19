#include "Simple_window.h" // 単純なウインドウ（[NEXT]ボタンが必要な場合）
#include "Graph.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main(){
	try{
		Point t1(100, 100);	// ウインドウの左上隅

		Simple_window win(t1, 600, 400, "Canvas");
		// 左上隅の画面座標t1
		// ウインドウサイズ（600×400）
		// タイトル : Canvas

		win.wait_for_button();		// 表示！

		Axis xa(Axis::x, Point(20, 300), 280, 10, "x axis");	// Axisを作成する
		// AxisはShapeの一種である
		// Axis::xは水平を意味する
		// (20, 300)から始まる
		// 長さは280ピクセルである
		// 刻み目は10個である
		// 軸に"x axis"というラベルを付ける

		win.attach(xa);				// xaをウインドウwinに関連付ける
		win.set_label("Canvas #2");	// ウインドウのラベルを付け直す
		win.wait_for_button();		// 表示！

		Axis ya(Axis::y, Point(20, 300), 280, 10, "y axis");
		ya.set_color(Color::cyan);				// 色を選択する
		ya.label.set_color(Color::dark_red);	// テキストの色を選択する
		win.attach(ya);
		win.set_label("Canvas #3");
		win.wait_for_button();		// 表示！
	}
	catch (exception& e){
		// エラーの報告
		cerr << e.what() << endl;
		return 1;
	}
	catch (...){
		// 別のエラーの報告
		return 2;
	}
}