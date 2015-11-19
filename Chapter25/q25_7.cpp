#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	// [0, 400]
	for(int i = 0; i <= 400; ++i)
		cout << hex << i << ' ';
	cout << endl;

	// [-200, 200]
	for(int i = -200; i <= 200; ++i)
		cout << hex << i << ' ';
	cout << endl;
}