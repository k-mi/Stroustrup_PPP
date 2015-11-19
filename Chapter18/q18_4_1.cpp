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

// Cスタイルの文字列を比較する
// s1が辞書式順序でs2の前にあれば負の数字、
// 後にあれば正の数字、等しければ0を返す
int strcmp(const char* s1, const char* s2){
	while(*s1 != '\0' || *s2 != '\0'){
		char c1 = *s1;
		char c2 = *s2;
		if('A' <= c1 && c1 >= 'Z') c1 -= 32;	// 小文字に変換
		if('A' <= c2 && c2 >= 'Z') c2 -= 32;	// 小文字に変換

		if(c1 < c2) return -1;
		else if(c1 > c2) return 1;
		++s1;
		++s2;
	}

	if(*s1 == '\0' && *s2 == '\0') return 0;
	else if(*s1 == '\0') return -1;
	else return 1;
}

int main(){
	char fake_str1[5] = { 'a', 'b', 'c', 'd', 'e' };
	char fake_str2[2] = { 'c', 'd' };

	char* p = strdup(fake_str2);
	cout << p << endl;
	delete[] p;

	p = findx(fake_str1, fake_str2);
	if(p != nullptr) cout << p << endl;
	delete[] p;

	int result = strcmp(fake_str1, fake_str2);
	if(result < 0) cout << "<" << endl;
	else if(result > 0) cout << ">" << endl;
	else cout << "==" << endl;
}