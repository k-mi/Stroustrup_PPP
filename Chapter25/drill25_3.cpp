#include <iostream>
using namespace std;

int main(){
	// 3
	short unsigned int a = 0xFFFF;
	short unsigned int b = 0x0001;
	short unsigned int c = 0x8000;
	short unsigned int d = 0x00FF;
	short unsigned int e = 0xFF00;
	short unsigned int f = 0x5555;
	short unsigned int g = 0xAAAA;

	// 4
	cout << "a: " << dec << a << ' ' << hex << a << endl;
	cout << "b: " << dec << b << ' ' << hex << b << endl;
	cout << "c: " << dec << c << ' ' << hex << c << endl;
	cout << "d: " << dec << d << ' ' << hex << d << endl;
	cout << "e: " << dec << e << ' ' << hex << e << endl;
	cout << "f: " << dec << f << ' ' << hex << f << endl;
	cout << "g: " << dec << g << ' ' << hex << g << endl;
}