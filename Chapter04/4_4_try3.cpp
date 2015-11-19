#include "std_lib_facilities.h"

int main(){
	char c = 'a';
	while(c <= 'z'){
		cout << c << '\t' << (int)c << endl;
		++c;
	}
}