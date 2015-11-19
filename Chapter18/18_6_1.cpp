#include <iostream>
using namespace std;

bool is_palindrome(const string& s){
	int first = 0;				// 最初の文字のインデックス
	int last = s.length() - 1;	// 最後の文字のインデックス

	while(first < last){		// まだ真ん中ではない
		if(s[first] != s[last]) return false;
		++first;				// 前方へ進む
		--last;					// 後方へ戻る
	}
	return true;
}

int main(){
	string s;
	while(cin >> s){
		cout << s << " is";
		if(!is_palindrome(s)) cout << " not";
		cout << " a palindrome\n";
	}
}