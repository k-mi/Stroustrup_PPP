#include "std_lib_facilities.h"

int main(){
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

	string input;
	while(cin >> input){
		int num = atoi(input.c_str());
		if((num > 0 && num <= 9) || (num == 0 && input[0] == '0'))
			cout << numbers[num] << endl;
		else
			for(int i = 0; i < numbers.size(); ++i)
				if(numbers[i] == input)
					cout << i << endl;			
	}
}