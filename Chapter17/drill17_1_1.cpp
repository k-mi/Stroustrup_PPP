#include <iostream>
using namespace std;

int main(){
	const int size = 10;
	
	int* array = new int[size];
	for(int i = 0; i < size; ++i)
		array[i] = i;

	for(int i = 0; i < size; ++i)
		cout << array[i] << endl;

	delete[] array;	
}