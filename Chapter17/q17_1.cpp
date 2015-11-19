#include <iostream>
using namespace std;

int main(){
	int* p = new int(5);
	cout << p << ' ' << hex << reinterpret_cast<long long>(p) << endl;
}