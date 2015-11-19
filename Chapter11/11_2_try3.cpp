#include <iostream>
using namespace std;

// fixedとscientificを間保する
inline ios_base& general(ios_base& b){
	// 浮動小数点数のフォーマットフラグをすべてクリアする
	b.setf(ios_base::fmtflags(0), ios_base::floatfield);
	return b;
}

int main(){
	const double num = 123456.78;

	cout << num << '\t' << endl
		 << fixed << num << '\t' << endl
		 << scientific << num << '\t' << endl
		 << general << num << '\t' << endl;
}