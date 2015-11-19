#include <iostream>
#include <cstring>	// stdlen
using namespace std;

// firstは最初の文字、lastは最後の文字をポイントする
bool is_palindrome(const char* first, const char* last){
	while(first < last){
		if(*first != *last) return false;
		return is_palindrome(first + 1, last - 1);
	}
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
		if(!is_palindrome(&s[0], &s[strlen(s) - 1])) cout << " not";
		cout << " a palindrome\n";
	}
}