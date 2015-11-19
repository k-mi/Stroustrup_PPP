#include <iostream>
#include <cstring>	// strlen
using namespace std;

// firstは最初の文字、lastは最後の文字をポイントする
bool is_palindrome(const char* first, const char* last){
	int size = 0;
	for(const char* p = first; p <= last; ++p)
		size++;

	int i = 0;
	char* back = new char[size];
	for(const char* p = last; p >= first; --p){
		*(back + i) = *p;
		++i;
	}

	char* q = back;
	for(const char* p = first; p <= last; ++p){
		if(*p != *q){
			delete[] back;
			return false;
		}
		++q;
	}
	delete[] back;
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