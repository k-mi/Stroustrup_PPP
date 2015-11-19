#include <iostream>
#include <cstring>
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