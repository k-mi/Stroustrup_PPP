#include "std_lib_facilities.h"

int main(){
	const double cm_per_inch = 2.54;	// 1インチあたりのセンチメートル
	double length = 1;					// インチまたはセンチメートルでの長さ
	char unit = ' ';
	cout << "Please enter a length followed by a unit (c or i):\n";
	cin >> length >> unit;

	switch(unit){
		case 'i':
			cout << length << "in == " << cm_per_inch * length << "cm\n";
			break;
		case 'c':
			cout << length << "cm == " << length / cm_per_inch << "in\n";
			break;
		default:
			cout << "Sorry, I don't know a unit called '" << unit << "'\n";
			break;
	}
}