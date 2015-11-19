#include <iostream>
using namespace std;

// メモリ割り当てが失敗するまで実行する
int main(){
	for(int i = 0; ; ++i){
		char* p = new char[1048576];
		for(int j = 0; j < 1048576; ++j)
			p[j] = j % 256;
		cout << i << "MB" << endl;
	}
}