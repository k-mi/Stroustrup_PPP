#include <iostream>
using namespace std;

int main(){
	string s = "          ";
	char tmp;

	for(int i = 0; cin >> tmp && tmp != '!'; ++i)
		s[i] = tmp;	

	cout << s << endl;
	cout << s.c_str() << endl;
}