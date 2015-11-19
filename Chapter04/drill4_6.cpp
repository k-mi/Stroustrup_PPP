#include "std_lib_facilities.h"
#include <limits>

int main(){
	double val, min = numeric_limits<double>::max(), max = numeric_limits<double>::min();

	while(cin >> val){	
		cout << val << endl;

		if(val < min){
			cout << "the smallest so far" << endl;
			min = val;
		}
		if(val > max){
			cout << "the largest so far" << endl;
			max = val;			
		}
	}
}