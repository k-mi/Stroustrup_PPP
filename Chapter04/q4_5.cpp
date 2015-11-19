#include "std_lib_facilities.h"

double mod(double a, double b){
	int tmp = a / b;
	return a - tmp * b;
}

int main(){
	double val1, val2;
	char operation;
	cin >> val1 >> val2 >> operation;

	switch(operation){
		case '+':
			cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << endl;
			break;
		case '-':
			cout << "The sub of " << val1 << " and " << val2 << " is " << val1 - val2 << endl;
			break;	
		case '*':
			cout << "The mul of " << val1 << " and " << val2 << " is " << val1 * val2 << endl;
			break;	
		case '/':
			cout << "The div of " << val1 << " and " << val2 << " is " << val1 / val2 << endl;
			break;	
		case '%':
			cout << "The mod of " << val1 << " and " << val2 << " is " << mod(val1, val2) << endl;
			break;
	}
}