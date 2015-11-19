#include <iostream>
using namespace std;

int main(){
	int v = 1;

	for(int i = 0; i < sizeof(v) * 8; ++i){
		cout << v << ' ';
		v <<= 1;
	}
}