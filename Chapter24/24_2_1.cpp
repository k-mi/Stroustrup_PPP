#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	float x = 1.0 / 333;
	float sum = 0;
	for(int i = 0; i < 333; ++i) sum += x;

	cout << sum << '\n';	// floatの有効桁数(7桁)でも1にならない
	cout << setprecision(15) << sum << '\n';
}