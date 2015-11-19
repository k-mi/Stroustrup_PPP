// 0以上100未満の偶数値の二乗を計算して出力する

#include "std_lib_facilities.h"

int square(int n){
	return pow(n, 2);
}

int main(){
	for(int i = 0; i < 100; i+=2)
		cout << i << '\t' << square(i) << '\n';
}