#include <iostream>
#include <cctype>
using namespace std;

int main(){
	string str;
	while(cin >> str){
		for(int i = 0; i < str.size(); ++i){
			cout << str[i] << ": ";
			if(isalpha(str[i])) cout << "英字 ";
			if(isdigit(str[i])) cout << "10進数字 ";
			if(isxdigit(str[i])) cout << "16進数字 ";
			if(isupper(str[i])) cout << "大文字 ";
			if(islower(str[i])) cout << "小文字 ";
			if(isalnum(str[i])) cout << "英数字 ";
			if(ispunct(str[i])) cout << "記号 ";
			if(isprint(str[i])) cout << "表示可能文字 ";
			if(isgraph(str[i])) cout << "英数記号";
			cout << endl;
		}
		cout << endl;
	}	
}