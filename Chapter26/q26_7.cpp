// 簡単なテキストエディタ部分は20_6_3.cppより

#include <iostream>
#include <fstream>
#include <algorithm> 	// find
#include <vector>
#include <list>
#include <stdexcept>	// runtime_error
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

/*
	ここから下にfind_txtのテストコードを追加

	フォーマット: <label, res>text</>
	label: テスト名
	res: 結果（0: false, 1: true）
	text: 検索する文字列（改行可）

	（例）
	<test01, 1>Apple
	Banana</test01>
*/

struct Test{
	string label;
	string text;
	bool res;
};

istream& operator>>(istream& is, Test& t){
	if(!is) return is;

	string label = "";
	string text = "";
	bool res;
	char ch1 = 0, ch2 = 0, tmp = 0;

	is >> ch1;
	if(ch1 != '<') return is;

	while(is.get(tmp) && tmp != ',')
		label += tmp;
	is >> res >> ch2;
	if(ch2 != '>') throw runtime_error("Syntax error");

	char ch3 = 0, ch4 = 0;
	while(is.get(tmp)){
		if(tmp == '<'){
			is.get(ch3);
			is.get(ch4);
			if(ch3 == '/' && ch4 == '>'){	
				t.label = label;
				t.text = text;
				t.res = res;
				return is;
			}
			else{
				is.putback(ch4);
				is.putback(ch3);
			}	
		}
		text += tmp;
	}

	// ここには来ない
	throw runtime_error("Syntax error");
}

int test_find_text(ifstream& ifs, Document& doc){
	Test test;
	int error_count = 0;

	while(ifs >> test){
		Text_iterator p = find_txt(doc.begin(), doc.end(), test.text);
		if((test.res && p == doc.end()) || (!test.res && p != doc.end())){
			cout << "failed: " << test.label << " -> " << test.res << endl;
			++error_count;
		}
	}

	return error_count;
}

int main(){
	Document my_doc;
	string filename1, filename2;
	cout << "input textfile: ";
	cin >> filename1;
	cout << "input testfile: ";
	cin >> filename2;

	ifstream ifs1(filename1.c_str());
	ifstream ifs2(filename2.c_str());
	if(!ifs1 || !ifs2){
		cerr << "input file can't open" << endl;
		return 1;
	}

	ifs1 >> my_doc;
	int errors = test_find_text(ifs2, my_doc);
	cout << "number of error: " << errors << endl;
}