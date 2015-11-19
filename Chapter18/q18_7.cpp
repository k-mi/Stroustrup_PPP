#include <iostream>
using namespace std;

char* cat_dot(const char* s1, const char* s2, char cat = '.'){
	int size_s1 = 0, size_s2 = 0;
	for(size_s1 = 0; s1[size_s1] != '\0'; ++size_s1);
	for(size_s2 = 0; s2[size_s2] != '\0'; ++size_s2);

	char* p = new char[size_s1 + size_s2 + 2];
	for(int i = 0; i < size_s1; ++i)
		p[i] = s1[i];
	p[size_s1] = cat;
	for(int i = 0; i < size_s2; ++i)
		p[size_s1 + i + 1] = s2[i];
	p[size_s1 + size_s2 + 2] = '\0';
	return p;
}

int main(){
	char* p = cat_dot("Niels", "Bohr", '-');
	cout << p << endl;
	delete[] p;
}