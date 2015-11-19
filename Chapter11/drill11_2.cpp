// Test_output.cpp
#include <iostream>
using namespace std;

int main(){
	int birth_year;
	cout << "生まれた年を入力してください。 > ";
	cin >> birth_year;

	cout << birth_year << "\tdec" << endl
		 << hex << birth_year << "\thex" << endl
		 << oct << birth_year << "\toct" << endl;
}