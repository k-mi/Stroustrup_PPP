#include <iostream>
using namespace std;

int main(){
	int x = 7;
	int* p1 = &x;

	cout << "p1: " << p1 << ' ' << *p1 << endl;
}