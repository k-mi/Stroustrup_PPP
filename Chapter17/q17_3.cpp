#include <iostream>
using namespace std;

// 大文字を小文字に置き換える
void to_lower(char* s){
	for(int i = 0; s[i] != '\0'; ++i){
		if('A' <= s[i] && s[i] <= 'Z')
			s[i] = s[i] + 32;
	}
}

int main(){
	char s[] = "Hello, World!";
	cout << s << endl;
	
	to_lower(s);
	cout << s << endl;
}