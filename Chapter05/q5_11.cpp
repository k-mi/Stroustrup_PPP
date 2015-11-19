#include "std_lib_facilities.h"
#include <limits>

// 再帰版
int fibonacci_recursion(int n){
	if(n > 2)
		return fibonacci_recursion(n-2) + fibonacci_recursion(n-1);

	return 1;
}

int fibonacci(int n){
	int a = 1, b = 1, t;

	if(n > 2){
		for(int i = 0; i < n; ++i){
			t = a + b;
			a = b;
			b = t;
		}
		return t;		
	}
	else
		return 1;
}

int main(){
	for(int i = 1; fibonacci(i) >= 1; ++i)
		cout << i << ": " << fibonacci(i) << endl;
}