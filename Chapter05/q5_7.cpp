#include "std_lib_facilities.h"

int main(){
	int a, b, c;
	cin >> a >> b >> c;

	if(a != 0){
		int d = b * b - 4 * a * c;	// 判別式

		if(d < 0)
			cout << "解はありません。" << endl;
		else if(d == 0)
			cout << "x = " << -b / 2 * a << endl;
		else
			cout << "x = " << (-b + sqrt(d)) / 2 * a << ", " <<  (-b - sqrt(d)) / 2 * a << endl;		
	}
	else{
		cout << "二次方程式ではありません。" << endl;
	}
}