#include <iostream>
#include <algorithm> // find
#include <vector>
#include <list>
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

void print(Document& d){
	for(Text_iterator p = d.begin(); p != d.end(); ++p)
		cout << *p;
}

// 2つの文字シーケンスを比較して、一致すればtrueを返す
template<class Iter> bool match(Iter p, Iter last, const string& s){
	int i = 0;
	for(Iter it = p; p != last && i < s.size(); ++it, ++i)
		if(*it != s[i]) return false;
	return true;
}

// GCC5.2でfindがコンパイルエラーとなるため、こちらを使用
template< class InputIt, class T >
InputIt find2(InputIt first, InputIt last, const T& value){
	while(first != last){
		if(*first == value) return first;
		++first;
	}
	return last;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s){
	if(s.size() == 0) return last;	// 空の文字列は検索できない
	char first_char = s[0];
	while(true){
		Text_iterator p = find2(first, last, first_char);
		if(p == last || match(p, last, s)) return p;
		first = ++p;
	}
}

int main(){
	Document my_doc;
	cin >> my_doc;

	Text_iterator p = find_txt(my_doc.begin(), my_doc.end(), "secret\nhomestead");
	if(p == my_doc.end())
		cout << "not found" << endl;
	else{
		// 何らかの処理
	}
}