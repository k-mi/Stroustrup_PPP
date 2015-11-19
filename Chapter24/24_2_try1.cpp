#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	float x = 1.0 / 10;
	float sum = 0;
	for(int i = 0; i < 10; ++i) sum += x;

	cout << sum << '\n';	// floatの有効桁数(7桁)では1になる
	cout << setprecision(15) << sum << '\n';
}