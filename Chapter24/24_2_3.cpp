#include <iostream>
#include <limits>	// numeric_limits
#include <climits>	// INT_MAX
using namespace std;

int main(){
	cout << "number of bytes in an int: " << sizeof(int) << '\n';
	cout << "largest int: " << INT_MAX << endl;
	cout << "smallest int value: " << numeric_limits<int>::min() << '\n';

	if(numeric_limits<char>::is_signed)
		cout << "char is signed\n";
	else
		cout << "char is unsigned\n";

	cout << "char with min value: " << numeric_limits<char>::min() << '\n';
	cout << "min char value: " << int(numeric_limits<char>::min()) << '\n';
}