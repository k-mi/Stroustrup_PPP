#include "std_lib_facilities.h"
#include <limits>

int area(int length, int width){
	if(length <= 0 || width <= 0) return -1;
	return length * width;
}

int framed_area(int x, int y){
	const int frame_width = 2;
	if(x - frame_width <= 0 || y - frame_width <= 0)
		error("non-positive area() argument called by framed_area()");
	return area(x - frame_width, y - frame_width);
}

void f(int x, int y, int z){
	int area1 = area(x, y);
	if(area1 <= 0) error("non-positive area");
	int area2 = framed_area(1, z);
	int area3 = framed_area(y, z);
	double ratio = double(area1)/area3;
}

int main(){
	// 最小値
	cout << area(1, 1) << endl;
	cout << framed_area(3, 3) << endl;

	// 最大値
	cout << area(numeric_limits<int>::max(), numeric_limits<int>::max()) << endl;
	cout << framed_area(numeric_limits<int>::max(), numeric_limits<int>::max()) << endl;

	// 失敗
	cout << area(0, 1) << endl;			// -1を返す
	cout << framed_area(2, 3) << endl;	// non-positive area() argument
	f(0, 0, 0);							// non-positive area()

}