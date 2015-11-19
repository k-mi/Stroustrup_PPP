// インチとセンチメートルの変換
// サフィックスの'i'と'c'は入力の単位を表す

#include "std_lib_facilities.h"

int main(){
	const double cm_per_inch = 2.54;	// 1インチあたりのセンチメートル
	double length = 1;					// インチまたはセンチメートルでの長さ
	char unit = 0;
	cout << "Please enter a length followed by a unit (c or i):\n";
	cin >> length >> unit;

	if(unit == 'i')
		cout << length << "in == " << cm_per_inch * length << "cm\n";
	else
		cout << length << "cm == " << length / cm_per_inch << "in\n";	
}