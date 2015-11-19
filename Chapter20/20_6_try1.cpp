#include <iostream>
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

template<class Iter> void advance(Iter& p, int n){
	if(n >= 0)
		while(0 < n) { ++p; --n; }
	else
		while(0 > n) { --p; ++n; }
}

void erase_line_pos(Document& d, int n){
	if(n < 0 || d.line.size() - 1 <= n) return;
	list<Line>::iterator p = d.line.begin();
	advance(p, n);
	d.line.erase(p);
}

void erase_line_neg(Document& d, int n){
	if(n < 0 || d.line.size() - 1 <= n) return;
	list<Line>::iterator p = d.line.end();
	advance(p, -n - 2);		// 空行とend()の2つ分前方へ移動
	d.line.erase(p);
}

int main(){
	Document d;
	cin >> d;
	erase_line_pos(d, 0);	// 前から1番目の行を削除
	erase_line_neg(d, 0);	// 後から1番目の行を削除
	print(d);
}