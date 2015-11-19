#include <iostream>
#include <algorithm>	// copy()
#include <cstring>		// strlen()
#include <stdexcept>
using namespace std;

// sはn個の文字からなる配列の1番目をポイントする
bool is_palindrome(const char s[], int n){	// char s[]とchar* sは同じ
	int first = 0;			// 最初の文字のインデックス
	int last = n - 1;		// 最後の文字のインデックス

	while(first < last){	// まだ真ん中ではない
		if(s[first] != s[last]) return false;
		++first;			// 前方へ進む
		--last;				// 後方へ戻る
	}
	return true;
}

// isから最大でmax-1個の文字をbufferに読み取る
istream& read_word(istream& is, char* buffer, int max){
	char tmp[max+1];
	is.width(max+1);			// 最大でmaxより1文字余分に読み取れるようにする
	is >> tmp;

	if(strlen(tmp) >= max)		// maxを超えていれば、報告して終了する
		throw runtime_error("Error: too long string!");

	copy(tmp, tmp + max - 1, buffer);	// bufferにコピーする
	buffer[max - 1] = '\0';

	return is;
}

int main(){
	const int max = 128;		// 入力できる最大文字数 + 1
	char s[max];
	while(read_word(cin, s, max)){
		cout << s << " is";
		if(!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}
}