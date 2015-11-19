#include <iostream>
using namespace std;

void print_array10(ostream& os, int* a){
	const int size = 10;

	for(int i = 0; i < size; ++i)
		os << a[i] << ' ';
	os << endl;
}

int main(){
	const int size = 11;
	
	int* array = new int[size];
	for(int i = 0; i < size; ++i)
		array[i] = i + 100;

	print_array10(cout, array);	// 最後の要素"110"が出力されない

	delete[] array;	
}