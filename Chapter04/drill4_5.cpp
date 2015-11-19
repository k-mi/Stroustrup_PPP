#include "std_lib_facilities.h"

int main(){
	double val1, val2;
	while(cin >> val1 >> val2){	
		if(val1 > val2){
			cout << "the smaller value is " << val2 << endl;
			cout << "the larger value is " << val1 << endl;
		}
		else{
			cout << "the smaller value is " << val1 << endl;
			cout << "the larger value is " << val2 << endl;			
		}

		if(val1 == val2)
			cout << "the numbers are erual" << endl;
		else if(abs(val1 - val2) < 1.0 / 10000000)
			cout << "the numbers are almost equal" << endl;
	}
}