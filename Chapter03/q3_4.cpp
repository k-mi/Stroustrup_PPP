#include "std_lib_facilities.h"

int main(){
	int val1, val2;
	cin >> val1 >> val2;

	if(val1 > val2){
		cout << "最大値: " << val1 << endl;
		cout << "最小値: " << val2 << endl;
	} 
	else{
		cout << "最大値: " << val2 << endl;
		cout << "最小値: " << val1 << endl;
	}

	cout << "和: " << val1 + val2 << endl;
	cout << "差: " << val1 - val2 << endl;
	cout << "積: " << val1 * val2 << endl;
	cout << "商: " << val1 / val2 << endl;
}