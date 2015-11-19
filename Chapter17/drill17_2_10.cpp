#include <iostream>
using namespace std;

void print_array(ostream& os, int* a, int n){
	for(int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << endl;
}

int main(){
	const int size = 10;
	int array[size];
	for(int i = 0, tmp = 1; i < size; ++i, tmp *= 2)
		array[i] = tmp;
	int* p1 = array;

	cout << "p1: " << p1 << ' ';	
	print_array(cout, p1, size);
}