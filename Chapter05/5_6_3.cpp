#include "std_lib_facilities.h"
// #include <stdexcept>

int main(){
	try{
		// 何らかの処理
		vector<int> v(5);
		v[5] = 0;

		return 0;	// 0は成功を示す
	} catch(exception& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;	// 1は失敗を示す
	} catch(...){
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;	// 1は失敗を示す		
	}
}