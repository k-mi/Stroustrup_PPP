#include <iostream>
using namespace std;

int main(){
	const int year = 2009;
	const int age = 6;

	cout << year << "\t(decimal)" << endl
		 << hex << year << "\t(hexadecimal)" << endl
		 << oct << year << "\t(octal)" << endl;

	cout << dec << age << "\t(decimal)" << endl
	 << hex << age << "\t(hexadecimal)" << endl
	 << oct << age << "\t(octal)" << endl;
}