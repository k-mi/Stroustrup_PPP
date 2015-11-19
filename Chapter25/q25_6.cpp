#include <iostream>
#include <limits>
using namespace std;

int main(){
	for(short i = 0; i <= numeric_limits<short>::max(); ++i){
		cout << "infinite loop: " << i << endl;
	}
}