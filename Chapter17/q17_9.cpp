#include <iostream>
using namespace std;

int main(){
	char stack_0;
	char stack_1;
	char* heep = new char[2];

	// MacOSの場合スタックは上位アドレスに向かって伸びる
	cout << "stack: " << endl
		<< reinterpret_cast<long long>(&stack_0) << endl
		<< reinterpret_cast<long long>(&stack_1) << endl;

	// MacOSの場合フリーストア（ヒープ）は下位アドレスに向かって伸びる
	cout << "heep: " << endl
		<< reinterpret_cast<long long>(heep) << endl
		<< reinterpret_cast<long long>(heep+1) << endl;

	delete[] heep;
}