#include "std_lib_facilities.h"

int main(){
	int a = 20000;
	char c = a;	// intをそれよりも小さいcharに縮小する
	int b = c;
	if(a != b) 	// !=は「等しくない」を意味する
		cout << "oops!: " << a << "!=" << b << '\n';
	else
		cout << "Wow! We have large characters\n";
}