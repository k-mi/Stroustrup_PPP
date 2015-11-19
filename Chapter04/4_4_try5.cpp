#include "std_lib_facilities.h"

int square(int v){
	int result = 0;

	for(int i = 0; i < v; ++i)
		result += v;

	return result;
}

int main(){
	for(int i = 0; i < 100; ++i)
		cout << i << '\t' << square(i) << endl;
}