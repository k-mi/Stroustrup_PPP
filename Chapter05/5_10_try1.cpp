#include "std_lib_facilities.h"

int area(int length, int width)
// 四角形の面積を計算する
// 事前条件: lengthとwidthは正
// 事後条件: 面積を表す正の値を返す
{
	if(length <= 0 || width <= 0) error("area() pre-condition");
	int a = length * width;
	if(a <= 0) error("area() post-condition");
	return a;
}

int main(){
	cout << area(1000000, 1000000) << endl;
}