#include <iostream>
#include <cstring>
using namespace std;

// sはn個の文字からなる配列の1番目をポイントする
bool is_palindrome(const char s[], int n){	// char s[]とchar* sは同じ
	const int max = 128;
	char back[max];
	for(int i = 0; i < n; ++i)
		back[i] = s[n - i - 1];

	for(int i = 0; i < n; ++i)
		if(s[i] != back[i])
			return false;
	return true;
}

// isから最大でmax-1個の文字をbufferに読み取る
istream& read_word(istream& is, char* buffer, int max){
	is.width(max);	// 次の>>で、最大でmax-1個の文字を読み取る
	is >> buffer;	// ホワイトスペースで区切られた単語を読み取り、
					// bufferの最後の文字の後に0を追加する
	return is;
}

int main(){
	const int max = 128;
	char s[max];
	while(read_word(cin, s, max)){
		cout << s << " is";
		if(!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}
}