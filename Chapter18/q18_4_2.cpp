#include <iostream>
using namespace std;

// Cスタイルの文字列をフリーストアで割り当てたメモリにコピーする
char* strdup(const char* str, int n){
	int size = 0;	// 文字数（'\0'は除く）
	for(size = 0; *(str + size) != '\0' && size < n - 1; ++size);
	
	char* p = new char[size + 1];
	for(int i = 0; i < size + 1; ++i)
		*(p + i) = *(str + i);

	return p;
}

// sに含まれている最初のCスタイルの文字列xを検索する
char* findx(const char* s, const char* x, int n1, int n2){
	int s_index = 0, x_index = 0;

	while(*(s + s_index) != '\0' && s_index < n1){
		if(*(s + s_index) == *(x + x_index)){	// 一致
			++s_index;
			++x_index;
			if(*(x + x_index) == '\0' || x_index == n2) 
				return strdup(s + s_index - x_index, s_index - x_index + 1); 
		}
		else{									// 不一致
			s_index += 1 - x_index;
			x_index = 0;
		}
	}
	return nullptr;
}

// Cスタイルの文字列を比較する
// s1が辞書式順序でs2の前にあれば負の数字、
// 後にあれば正の数字、等しければ0を返す
int strcmp(const char* s1, const char* s2, int n1, int n2){
	int s1_index = 0, s2_index = 0;

	while((*(s1 + s1_index) != '\0' && s1_index < n1) 
		|| (*(s2 + s2_index) != '\0' && s2_index < n2)){
		char c1 = *(s1 + s1_index);
		char c2 = *(s2 + s2_index);
		if('A' <= c1 && c1 >= 'Z') c1 -= 32;	// 小文字に変換
		if('A' <= c2 && c2 >= 'Z') c2 -= 32;	// 小文字に変換

		if(c1 < c2) return -1;
		else if(c1 > c2) return 1;
		++s1_index;
		++s2_index;
	}

	if((*(s1 + s1_index) == '\0' || s1_index == n1) 
		&& (*(s2 + s2_index) == '\0' || s2_index == n2)) return 0;
	else if(*(s1 + s1_index) == '\0' || s1_index == n1) return -1;
	else return 1;
}

int main(){
	string str1 = "abcde";
	string str2 = "cd";
	char fake_str1[5] = { 'a', 'b', 'c', 'd', 'e' };
	char fake_str2[2] = { 'c', 'd' };

	// fake
	char* p = strdup(fake_str2, 2);
	cout << p << endl;
	delete[] p;

	p = findx(fake_str1, fake_str2, 5, 2);
	if(p != nullptr) cout << p << endl;
	delete[] p;

	int result = strcmp(fake_str1, fake_str2, 5, 2);
	if(result < 0) cout << "<" << endl;
	else if(result > 0) cout << ">" << endl;
	else cout << "==" << endl;

	// right
	char* q = strdup(str2.c_str(), 10);
	cout << q << endl;
	delete[] q;

	q = findx(str1.c_str(), str2.c_str(), 10, 10);
	if(q != nullptr) cout << q << endl;
	delete[] q;

	result = strcmp(str1.c_str(), str2.c_str(), 10, 10);
	if(result < 0) cout << "<" << endl;
	else if(result > 0) cout << ">" << endl;
	else cout << "==" << endl;
}