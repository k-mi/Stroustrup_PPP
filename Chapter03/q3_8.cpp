#include "std_lib_facilities.h"

int main(){
	int val;
	cin >> val;

	if(val % 2 == 0)
		cout << "値" << val << "は偶数である" << endl;
	else
		cout << "値" << val << "は奇数である" << endl;
}