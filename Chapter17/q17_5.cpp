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

// sから最初のCスタイルの文字列xを検出する
char* findx(const char* s, const char* x){
	int x_size = 0, j = 0;
	for(int i = 0; x[i] != '\0'; ++i, ++j){
		if(s[j] == '\0') return 0;
		if(s[j] != x[i]){
			j -= i;
			i = -1;
		}
		x_size = i;
	}
	return strdup(&s[j - x_size - 1]);
}

int main(){
	char s[] = "Hello, World!";
	char x[] = "W";

	char* result = findx(s, x);
	if(result != 0) cout << result << endl;
	delete[] result;
}