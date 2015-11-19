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
		win.wait_for_button();	// 表示！
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