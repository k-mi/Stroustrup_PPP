#include "std_lib_facilities.h"

int main(){
	int x, y, z;
	cin >> x >> y >> z;

	if(x < y){
		if(y < z)
			cout << x << ", " << y << ", " << z << endl;
		else{
			if(x > z)
				cout << z << ", " << x << ", " << y << endl;
			else
				cout << x << ", " << z << ", " << y << endl;
		}
	}
	else{
		if(y > z)
			cout << z << ", " << y << ", " << x << endl;
		else{
			if(x > z)
				cout << y << ", " << z << ", " << x << endl;
			else
				cout << y << ", " << x << ", " << z << endl;
		}
	}
}