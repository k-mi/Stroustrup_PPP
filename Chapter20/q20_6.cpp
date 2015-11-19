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

	// 追加: replace_txt()で使用
	list<Line>::iterator get_line() { return ln; }
	Line::iterator get_pos() { return pos; }

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
// 検索置換操作
// [first:end)の最初のold_sを検索し、new_sと置換
void replace_txt(Text_iterator first, Text_iterator last, const string& old_s, const string& new_s){
	Text_iterator p = find_txt(first, last, old_s);
	if(p == last) return;	// 見つからない場合終了

	// 挿入によりLine::iteratorは無効になるため、インデックスを保持
	// 初期値は、検索した先頭文字に相当するp
	int index = p.get_pos() - (*p.get_line()).begin();
	for(int i = 0; i < new_s.size(); ++i){
		if(old_s.size() > i){
			*p = new_s[i];

			// vectorの終端に達した場合、インデックスをリセット
			index = p.get_pos() == --(*p.get_line()).end() ? 0 : index + 1;
			
			++p;
		}
		else{ // old_sより長い場合はそのlineのvectorに新たに要素を挿入
			(*p.get_line()).insert((*p.get_line()).begin() + index, new_s[i]);
			index++; 
		}
	}

	// 余分な要素を削除
	list<Line>::iterator ln_it = p.get_line();	// lineのイテレータ
	Line::iterator pos_it = p.get_pos();		// posのイテレータ
	bool f = true;
	for(int i = old_s.size() - new_s.size(); i > 0; --i){
		if(pos_it == (*ln_it).end()){			// vectorの終端に達した場合、次のlistへ移動
			++ln_it;
			f = false;
		} 
		pos_it = f ? pos_it : (*ln_it).begin();	// 初回のlist以外ではvectorの最初を参照
		(*ln_it).erase(pos_it);
	}
}

void print(Document& d){
	for(Text_iterator p = d.begin(); p != d.end(); ++p)
		cout << *p;
}

int main(){
	Document my_doc;
	cin >> my_doc;

	replace_txt(my_doc.begin(), my_doc.end(), "App\nle", "Banana");
	print(my_doc);
}