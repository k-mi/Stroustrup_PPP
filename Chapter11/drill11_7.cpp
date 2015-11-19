// Test_output.cpp
#include <iostream>
using namespace std;

int main(){
	int birth_year;
	const int this_year = 2015;

	cout << "生まれた年を入力してください。 > ";
	cin >> birth_year;

	cout << showbase << birth_year << "\tdecimal" << endl
		 << hex << birth_year << "\thexadecimal" << endl
		 << oct << birth_year << "\toctal" << endl;

	int age = this_year - birth_year;
	cout << "年齢は" << dec << age << "です。" << endl;
}