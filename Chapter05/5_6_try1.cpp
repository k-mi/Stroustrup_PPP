#include "std_lib_facilities.h"
// #include <stdexcept>

class Except{};

int main(){
	try{
		throw Except();	// キャッチされない例外を投げる
		return 0;		// 0は成功を示す
	} catch(out_of_range& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;		// 1は失敗を示す
	}
}