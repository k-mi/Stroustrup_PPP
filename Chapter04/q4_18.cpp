#include "std_lib_facilities.h"

int main(){
	double a, b, c, x1, x2, tmp;
	cin >> a >> b >> c;

	tmp = b * b - 4 * a * c;
	if(tmp >= 0){
		x1 = (-b + sqrt(tmp)) / (2 * a);
		x2 = (-b - sqrt(tmp)) / (2 * a);
	}
	else{
		x1 = (-b - sqrt(-tmp)) / (2 * a);
		x2 = (-b + sqrt(-tmp)) / (2 * a);		
	}

	if(x1 == x2)
		cout << "x = " << x1 << endl;
	else
		cout << "x = " << x1 << ", " << x2 << endl;

}