#include <iostream>
using namespace std;

int main(){
	cout << "int is " << sizeof(int) * 8 << "bit" << endl;

	char c = 0xFF;
	int i = int(c);
	if(i == 0xFF) cout << "unsigned char" << endl;
	else cout << "signed char" << endl;
}