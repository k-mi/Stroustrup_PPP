// multi_input.cpp
#include <iostream>
using namespace std;

int main(){
	int i;
	char c;

	cin.unsetf(ios_base::dec);	// 10進数を前提としない
	cout << showbase;			// 基数を表示

	while(cin >> c){
		switch(c){
			case '0':
				cin >> c;
				switch(c){
					case 'x': case 'X':
						cin.unget();
						cin.putback('0');
						cin >> i;

						cout << hex << i << "\thexadicimal" << "\tconverts to\t"
							 << dec << i << "\tdecimal" << endl;
						break;

					default:
						cin.unget();
						cin.putback('0');
						cin >> i;

						cout << oct << i << "\toctal      " << "\tconverts to\t"
							 << dec << i << "\tdecimal" << endl;
						break;
				}
				break;
			default:
				cin.unget();
				cin >> i;
				cout << dec << i << "\tdecimal    " << "\tconverts to\t"
					 << dec << i << "\tdecimal" << endl;
				break;
		}
	}
}