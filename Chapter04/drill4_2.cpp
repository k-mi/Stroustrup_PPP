#include "std_lib_facilities.h"

int main(){
	int val1, val2;
	while(cin >> val1 >> val2){
		if(val1 > val2){
			cout << "the smaller value is " << val2 << endl;
			cout << "the larger value is " << val1 << endl;
		}
		else{
			cout << "the smaller value is " << val1 << endl;
			cout << "the larger value is " << val2 << endl;
		}
	}
}