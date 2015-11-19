#include "std_lib_facilities.h"

double mod(double a, double b){
	int tmp = a / b;
	return a - tmp * b;
}

int input(string str){
	vector<string> numbers(10);
	numbers[0] = "zero";
	numbers[1] = "one";
	numbers[2] = "two";
	numbers[3] = "three";
	numbers[4] = "four";
	numbers[5] = "five";
	numbers[6] = "six";
	numbers[7] = "seven";
	numbers[8] = "eight";
	numbers[9] = "nine";

	int num = atoi(str.c_str());
	if((num > 0 && num <= 9) || (num == 0 && str[0] == '0'))
		return num;
	else
		for(int i = 0; i < numbers.size(); ++i)
			if(numbers[i] == str)
				return i;

	return -1;			
}

int main(){
	string str1, str2;
	int val1, val2;
	char operation;

	cin >> str1 >> str2 >> operation;
	val1 = input(str1);
	val2 = input(str2);
	if(val1 == -1 || val2 == -1){
		cerr << "Input error!" << endl;
		exit(EXIT_FAILURE);
	}

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