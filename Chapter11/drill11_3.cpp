// Test_output.cpp
#include <iostream>
using namespace std;

int main(){
	int birth_year;
	cout << "生まれた年を入力してください。 > ";
	cin >> birth_year;

	cout << birth_year << "\tdecimal" << endl
		 << hex << birth_year << "\thexadecimal" << endl
		 << oct << birth_year << "\toctal" << endl;
}