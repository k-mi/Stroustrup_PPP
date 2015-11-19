#include "std_lib_facilities.h"

int main(){
	double val1, val2;
	string operation;
	cin >> operation >> val1 >> val2;

	if(operation == "+" || operation == "plus")
		cout << val1 + val2 << endl;
	else if(operation == "-" || operation == "minus")
		cout << val1 - val2 << endl;
	else if(operation == "*" || operation == "mul")
		cout << val1 * val2 << endl;
	else if(operation == "/" || operation == "div")
		cout << val1 / val2 << endl;
}