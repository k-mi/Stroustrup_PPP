#include <iostream>
using namespace std;

string cat_dot(const string& s1, const string& s2, char cat = '.'){
	return s1 + cat + s2;
}

int main(){
	cout << cat_dot("Niels", "Bohr", '-') << endl;
}