// 0〜99の二乗を計算して出力する

#include "std_lib_facilities.h"

int square(int n){
	return pow(n, 2);
}

int main(){
	int i = 0;	// 0から始める
	while(i < 100){
		cout << i << '\t' << square(i) << '\n';
		++i;	// iをインクリメントする（つまりi+1）
	}
}