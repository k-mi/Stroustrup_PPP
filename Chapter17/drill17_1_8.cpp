#include <iostream>
using namespace std;

void print_array(ostream& os, int* a, int n){
	for(int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << endl;
}

int main(){
	const int size = 20;
	
	int* array = new int[size];
	for(int i = 0; i < size; ++i)
		array[i] = i + 100;

	print_array(cout, array, size);

	delete[] array;	
}