#include <iostream>
using namespace std;

void print_array(ostream& os, int* a, int n){
	for(int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << endl;
}

int main(){
	int x = 7;
	int* p1 = &x;

	cout << "p1: " << p1 << ' ' << *p1 << endl;

	const int size = 7;
	int array[size];
	for(int i = 0, tmp = 1; i < size; ++i, tmp *= 2)
		array[i] = tmp;
	int* p2 = array;

	cout << "p2: " << p2 << ' ';	
	print_array(cout, p2, size);
}