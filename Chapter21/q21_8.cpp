#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_map>
using namespace std;

template<class T> struct Comp_second{
	bool operator()(const T& t1, const T& t2){
		return t1.second > t2.second;
	}
};

int main(){
	unordered_map<string, int> words;	// 単語と出現回数のペアを維持する
	string s;
	while(cin >> s) ++words[s];			// 注意: 単語の添え字は文字列

	vector< pair<string, int> > ordered_words(words.size());
	partial_sort_copy(words.begin(), words.end(), 
		ordered_words.begin(), ordered_words.end(), Comp_second< pair<string, int> >());
	
	typedef vector< pair<string, int> >::const_iterator Iter;
	for(Iter p = ordered_words.begin(); p != ordered_words.end(); ++p)
		cout << p->second << ": " << p->first << '\n';
}