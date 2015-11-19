#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	cout << "Sizes: " << sizeof(int) << ' ' << sizeof(float) << '\n';
	int x = 2100000009;	// 大きなint
	float f = x;
	cout << x << ' ' << f << endl;
	cout << setprecision(15) << x << ' ' << f << endl;
}