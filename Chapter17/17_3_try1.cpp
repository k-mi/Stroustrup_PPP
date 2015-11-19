#include <iostream>
using namespace std;

int main(){
	cout << "the size of char is " << sizeof(char) << ' ' << sizeof('a') << endl;
	cout << "the size of int is " << sizeof(int) << ' ' << sizeof(2+2) << endl;
	int *p = 0;
	cout << "the size of int* is " << sizeof(int*) << ' ' << sizeof(p) << endl;

	cout << "the size of bool is " << sizeof(bool) << ' ' << sizeof(true) << endl;
	cout << "the size of double is " << sizeof(double) << ' ' << sizeof(3.1415) << endl;
}