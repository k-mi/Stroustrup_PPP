#include <iostream>
using namespace std;

int main(){
	const unsigned int size = sizeof(short unsigned int) * 8;

	short unsigned int b = 1;
	short unsigned int c = 1 << size - 1;

	short unsigned int d = 0;
	for(int i = 0; i < size / 2; ++i)
		d |= 1 << i;

	short unsigned int e = d << (size / 2);
	short unsigned int a = d | e;
	
	short unsigned int f = 0;
	for(int i = 0; i < size; ++i)
		if(i % 2 == 0) f |= 1 << i;

	short unsigned int g = f << 1;

	cout << "a: " << dec << a << ' ' << hex << a << endl;
	cout << "b: " << dec << b << ' ' << hex << b << endl;
	cout << "c: " << dec << c << ' ' << hex << c << endl;
	cout << "d: " << dec << d << ' ' << hex << d << endl;
	cout << "e: " << dec << e << ' ' << hex << e << endl;
	cout << "f: " << dec << f << ' ' << hex << f << endl;
	cout << "g: " << dec << g << ' ' << hex << g << endl;
}