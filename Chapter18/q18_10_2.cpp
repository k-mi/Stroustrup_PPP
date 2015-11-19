#include <iostream>
#include <algorithm>	// copy()
#include <cstring>		// strlen(), memcpy()
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
bool read_word(istream& is, char* buffer, int max){
	char tmp[max+1];
	is.width(max+1);			// 最大でmaxより1文字余分に読み取れるようにする
	is >> tmp;

	if(strlen(tmp) >= max){		// maxを超えていれば、isに1文字戻す
		//cout << "too long string!" << endl;
		is.putback(tmp[max-1]);
		copy(tmp, tmp + max - 1, buffer);	// bufferにコピーする
		buffer[max - 1] = '\0';				// 最後にヌル文字を付ける
		return true;						// 続きがあればtrueを返す
	}

	copy(tmp, tmp + max - 1, buffer);		// bufferにコピーする
	buffer[max - 1] = '\0';					// 最後にヌル文字を付ける
	return false;							// 続きがなければfalseを返す
}

int main(){
	while(cin.good()){
		int max = 2;						// 最初に用意する文字数 + 1
		int index = 0;						// 現在位置
		char* r = new char[max];			// read_word()からの新規追加文字列
		char* s = new char[max * 2];		// 全体の文字列
		char* tmp = new char[max * 2];		// サイズ変更時の文字列の一時保持

		while(read_word(cin, r, max)){
			copy(r, r + max, s + index);	// rをsに追加
			index += max - 1;
			max *= 2;

			delete[] r;
			r = new char[max];
			copy(s, s + max, tmp);
			delete[] s;
			s = new char[max * 2];
			copy(tmp, tmp + max, s);
			delete[] tmp;
			tmp = new char[max * 2];
		}
		copy(r, r + max, s + index);		// rをsに追加

		cout << s << " is";
		if(!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";

		delete[] r;
		delete[] s;
		delete[] tmp;
	}
}