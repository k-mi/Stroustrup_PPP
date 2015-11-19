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

		Function sine(sin, 0, 100, Point(20, 150), 1000, 50, 50);	// 正弦曲線
		// (20. 150)の位置を(0, 0)として[0:100)の範囲でsin関数をプロットする
		// ポイントを1.000個使用する。x値×50、y値×50でスケーリングする

		win.attach(sine);
		win.set_label("Canvas #4");
		win.wait_for_button();		// 表示！

		sine.set_color(Color::blue);	// 正弦曲線の色を変更する

		Graph_lib::Polygon poly;		// ポリゴン : PolygonはShapeの一種である
		poly.add(Point(300, 200));
		poly.add(Point(350, 100));
		poly.add(Point(400, 200));

		poly.set_color(Color::red);
		poly.set_style(Line_style::dash);
		win.attach(poly);
		win.set_label("Canvas #5");
		win.wait_for_button();		// 表示！

		Graph_lib::Rectangle r(Point(200, 200), 100, 50);	// 左上隅、幅、高さ
		win.attach(r);

		Closed_polyline poly_rect;
		poly_rect.add(Point(100, 50));
		poly_rect.add(Point(200, 50));
		poly_rect.add(Point(200, 100));
		poly_rect.add(Point(100, 100));
		poly_rect.add(Point(50, 75));
		win.attach(poly_rect);
		win.set_label("Canvas #6");
		win.wait_for_button();		// 表示！

		r.set_fill_color(Color::yellow);	// 正方形内部の色
		poly.set_style(Line_style(Line_style::dash, 4));
		poly_rect.set_style(Line_style(Line_style::dash, 2));
		poly_rect.set_fill_color(Color::green);
		win.set_label("Canvas #7");
		win.wait_for_button();		// 表示！

		Text t(Point(150, 150), "Hello, graphical world! ");
		win.attach(t);
		win.set_label("Canvas #8");
		win.wait_for_button();		// 表示！

		t.set_font(Font::times_bold);
		t.set_font_size(20);
		win.set_label("Canvas #9");
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