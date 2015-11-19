#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef vector<char> Line;	// 行は文字のvector

struct Document{
	list<Line> line;		// ドキュメントは行のlist
	Document() { line.push_back(Line()); }
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

int main(){
	Document d;
	cin >> d;

	for(list<Line>::iterator it = d.line.begin(); it != d.line.end(); ++it)
		for(int i = 0; i < (*it).size(); ++i)
			cout << (*it)[i];
}