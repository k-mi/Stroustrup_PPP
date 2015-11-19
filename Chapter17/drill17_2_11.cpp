#include <iostream>
using namespace std;

void print_array(ostream& os, int* a, int n){
	for(int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << endl;
}

int main(){
	const int size = 10;
	int array1[size];
	for(int i = 0, tmp = 1; i < size; ++i, tmp *= 2)
		array1[i] = tmp;
	int* p1 = array1;

	int array2[size] = {0};
	int* p2 = array2;

	for(int i = 0; i < size; ++i)
		p2[i] = p1[i];

	cout << "p1: " << p1 << ' ';	
	print_array(cout, p1, size);

	cout << "p2: " << p2 << ' ';	
	print_array(cout, p2, size);
}