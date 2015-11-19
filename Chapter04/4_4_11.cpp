#include "std_lib_facilities.h"

int main(){
	vector<string> words;
	string temp;
	while(cin >> temp)			// ホワイトスペースで区切られた単語を読み取る
		words.push_back(temp);	// vectorに追加する

	cout << "Number of words: " << words.size() << endl;

	sort(words.begin(), words.end());	// wordsの最初から最後まで（昇順で）並び替える

	for(int i = 0; i < words.size(); ++i)
		if(i == 0 || words[i-1] != words[i])
			cout << words[i] << "\n";
}