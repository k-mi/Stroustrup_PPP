#include <iostream>
using namespace std;

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
	string s1, s2;
	cin >> s1 >> s2;

	int result = strcmp(s1.c_str(), s2.c_str());
	if(result < 0) cout << s1 << " < " << s2 << endl;
	else if(result > 0) cout << s1 << " > " << s2 << endl;
	else cout << s1 << " == " << s2 << endl;
}