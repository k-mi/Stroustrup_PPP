#include "std_lib_facilities.h"

int main(){
	cout << "Please enter expression (we can handle + and -): ";
	int lval = 0;
	int rval;
	char op;
	int res;
	cin >> lval >> op >> rval;	// 1 + 3 などを読み取る

	if(op == '+')
		res = lval + rval;		// 加算
	else if(op == '-')
		res = lval - rval;		// 減算

	cout << "Result: " << res << '\n';
	keep_window_open();

	return 0; 
}