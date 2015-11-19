#include <iostream>
using namespace std;

// フリーストアで割り当てたメモリのコピーする
char* strdup(const char* s){
	int size;
	for(size = 0; s[size] != '\0'; ++size);

	char* tmp = new char[size];
	for(int i = 0; i < size; ++i)
		tmp[i] = s[i];

	return tmp;
}

int main(){
	char s[] = "Hello, World!";
	cout << s << endl;

	char* result = strdup(s);
	cout << result << endl;

	delete[] result;
}