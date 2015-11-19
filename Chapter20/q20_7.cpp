#include <iostream>
#include <vector>
using namespace std;

// 最も大きな値を持つ[first,last)の範囲内の要素へのイテレータを返す
template<class Iter> Iter high(Iter first, Iter last){
	if(first == last) return last;
	Iter high = first;
	for(Iter it = first + 1; it != last; ++it)	// 次の要素から比較を開始
		if(*high < *it) high = it;
	return high;
}

int main(){
	vector<string> vs;
	vs.push_back("apple");
	vs.push_back("dount");
	vs.push_back("chocolate");
	vs.push_back("banana");

	cout << *high(vs.begin(), vs.end()) << endl;
}