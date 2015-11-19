#include "std_lib_facilities.h"
#include <limits>

int main(){
	int count = 0;

	for(int rise = 1, sum = 0; sum + rise < numeric_limits<int>::max(); rise *= 2){
		sum += rise;
		count++;
		//cout << sum << endl;
	}
	cout << "int: " << count << endl;;

	count = 0;

	for(double rise = 1, sum = 0; sum + rise < numeric_limits<double>::max(); rise *= 2){
		sum += rise;
		count++;
		//cout << sum << endl;
	}
	cout << "double: " << count << endl;	
}