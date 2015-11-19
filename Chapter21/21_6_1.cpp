#include <iostream>
#include <map>
using namespace std;

int main(){
	map<string, int> words;		// 単語と出現回数のペアを維持する

	string s;
	while(cin >> s) ++words[s];	// 注意: 単語の添え字は文字列

	typedef map<string, int>::const_iterator Iter;
	for(Iter p = words.begin(); p != words.end(); ++p)
		cout << p->first << ": " << p->second << '\n';
}