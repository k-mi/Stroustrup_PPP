#include "std_lib_facilities.h"

int main(){
	int min, count = 0, sum = 0;
	cin >> min;

	for(int rise = 1; sum < min; rise *= 2){
		sum += rise;
		++count;
		cout << count << " " << rise << " " << sum << endl;
	}

	cout << count << endl;
}