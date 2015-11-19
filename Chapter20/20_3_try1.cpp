#include <iostream>
using namespace std;

void copy(int* f1, int* e1, int* f2){
	for(int* p = f1; p != e1; ++p){
		*f2 = *p;
		++f2;
	}
}

int main(){
	int a[5] = {1, 2, 3, 4, 5};
	int b[5] = {0};

	copy(a, &a[5], b);

	for(int i = 0; i < 5; ++i)
		cout << a[i] << ' ' << b[i] << endl;
}