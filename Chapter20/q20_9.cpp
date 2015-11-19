#include <iostream>
#include <vector>
#include <list>
#include <cctype>	// isspace, isalpha
using namespace std;

typedef vector<char> Line;	// 行は文字のvector

// 行および行内での文字の位置を追跡する
class Text_iterator{
public:
	// 行llの文字位置ppでイテレータを開始する
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln(ll), pos(pp) { }

	char& operator*() { return *pos; }
	Text_iterator& operator++();

	bool operator==(const Text_iterator& other) const
	{ return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const
	{ return !(*this == other); }

private:
	list<Line>::iterator ln;
	Line::iterator pos;
};

Text_iterator& Text_iterator::operator++(){
	++pos;		// 次の文字へ進む
	if(pos == (*ln).end()){
		++ln;	// 次の行へ進む
		pos = (*ln).begin();
	}
	return *this;
}

struct Document{
	list<Line> line;		// ドキュメントは行のlist
	Document() { line.push_back(Line()); }

	Text_iterator begin()	// 最初の行の1行目
	{ return Text_iterator(line.begin(), (*line.begin()).begin()); }
	Text_iterator end()		// 最後の行の最後の文字の1つ後
	{
		list<Line>::iterator last = line.end();
		--last;				// ドキュメントが空でないことがわかっている
		return Text_iterator(last, (*last).end());
	}
};

istream& operator>>(istream& is, Document& d){
	char ch;
	while(is.get(ch)){
		d.line.back().push_back(ch);	// 最後のLine（空行）に文字を追加する
		if(ch == '\n')
			d.line.push_back(Line());	// 別の行を追加する
	}
	if(d.line.back().size()) 
		d.line.push_back(Line());		// 最後に空の行を追加する
	return is;
}

// ドキュメント内の単語（ホワイトスペースで区切られた文字列）数を返す
int count_word_ws(Document& d){
	int count = 0;
	bool is_space = true;
	for(Text_iterator p = d.begin(); p != d.end(); ++p) {
		if(isspace(*p)) is_space = true;
		else{
			if(is_space) ++count; 
			is_space = false;
		}
	}
	return count;
}

// ドキュメント内の単語（連続するアルファベットの文字列）数を返す
int count_word_alpha(Document& d){
	int count = 0;
	int type = 0;	// 0:others 1:isalpha 2:isdigit
	for(Text_iterator p = d.begin(); p != d.end(); ++p) {
		if(isalpha(*p)){
			if(type != 1) ++count;
			type = 1;
		}
		else if(isdigit(*p)){
			if(type != 2) ++count;
			type = 2;
		}
		else type = 0;
	}
	return count;
}

int main(){
	Document my_doc;
	cin >> my_doc;

	cout << "ws: " << count_word_ws(my_doc) << endl;
	cout << "alpha: " << count_word_alpha(my_doc) << endl;
}