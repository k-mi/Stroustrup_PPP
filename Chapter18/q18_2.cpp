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

// sに含まれている最初のCスタイルの文字列xを検索する
char* findx(const char* s, const char* x){
	const char* first = x;	// xの最初のポインタ

	while(*s != '\0'){
		if(*s == *x){	// 一致
			++s;
			++x;
			if(*x == '\0') return strdup(s - (x - first)); 
		}
		else{			// 不一致
			s += 1 - (x - first);
			x = first;
		}
	}
	return nullptr;
}

int main(){
	string s, x;
	cin >> s >> x;

	char* p = findx(s.c_str(), x.c_str());
	if(p != nullptr) cout << p << endl;
	delete[] p;
}