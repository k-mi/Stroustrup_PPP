#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace std;

// istreamと似ているが、ユーザが一連のホワイトスペース文字を追加できる
class Punct_stream{
public:
	Punct_stream(istream& is) : source(is), sensitive(true) { }
	void whitespace(const string& s) { white = s; }	// sをホワイトスペースにセットする
	void add_white(char c) { white += c; }			// ホワイトスペースセットに追加する
	bool is_whitespace(char c);	// cはホワイトスペースセットに含まれているか

	void case_sensitive(bool b) { sensitive = b; }
	bool is_case_sensitive() { return sensitive; }

	Punct_stream& operator>>(string& s);
	operator bool();

private:
	istream& source;		// 文字ソース
	istringstream buffer; 	// bufferにフォーマットを処理させる	
	string white;			// 「ホワイトスペース」と見なされる文字
	bool sensitive;			// ストリームは大文字小文字を区別するか
};

Punct_stream& Punct_stream::operator>>(string& s){
	while(!(buffer >> s)){	// bufferからの読み取りを試みる
		if(buffer.bad() || !source.good()) return *this;
		buffer.clear();	

		// bufferがeof()の場合、bufferを補充する
		string line;
		getline(source, line);	// sourceからlineを取得する

		// 必要に応じて文字を置き換える
		for(int i = 0; i < line.size(); ++i)
			if(is_whitespace(line[i]))
				line[i] = ' ';	// スペースに置き換える
			else if(!sensitive)
				line[i] = tolower(line[i]);	// 小文字に置き換える
		buffer.str(line);	// bufferの文字列をストリームに格納する
	}
	return *this;
}

bool Punct_stream::is_whitespace(char c){
	for(int i = 0; i < white.size(); ++i)
		if(c == white[i])
			return true;
	return false;
}

// Punct_streamをboolに暗黙的に変換
Punct_stream::operator bool(){
	return !(source.fail() || source.bad()) && source.good();
}

int main(){
	// 指定されたテキスト入力から、そのテキストに含まれているすべての単語の
	// ソート済みのリストを生成する
	// 句読点は無視し、大文字と小文字は区別しない
	// 出力から重複する単語を削除する

	Punct_stream ps(cin);		// psはcinを読み取る
	ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
	ps.case_sensitive(false);	// 大文字と小文字を区別しない

	cout << "please enter words" << endl;
	vector<string> vs;
	string word;
	while(ps >> word)			// 単語を読み取る
		vs.push_back(word);

	sort(vs.begin(), vs.end());	// 辞書式順序でソートする
	for(int i = 0; i < vs.size(); ++i)	// 辞書を書き出す
		if(i == 0 || vs[i] != vs[i-1])
			cout << vs[i] << endl;

	return 0;
}