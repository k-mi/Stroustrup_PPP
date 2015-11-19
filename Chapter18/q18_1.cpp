#include <iostream>
using namespace std;

// Cスタイルの文字列をフリーストアで割り当てたメモリにコピーする
char* strdup(const char* str){
	int size = 0;	// 文字数（'\0'は除く）
	for(size = 0; *(str + size) != '\0'; ++size);
	
	char* p = new char[size + 1];
	for(int i = 0; i < size + 1; ++i)
		*(p + i) = *(str + i);

	return p;
}

int main(){
	char *p = strdup("Apple");
	cout << p << endl;
	delete[] p;
}