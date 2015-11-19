#include <iostream>
#include <list>
using namespace std;

namespace sample{
	// ユーザが指定した条件に基づいて検索を行うアルゴリズム	
	template<class In, class Pred> In find_if(In first, In last, Pred pred){
		while(first != last && !pred(*first)) ++first;
		return first;
	}	
}

class Larger_than {
public:
	Larger_than(int vv) : v(vv) { }					// 引数を格納する
	bool operator()(int x) const { return x > v; }	// 比較する

private:
	int v;
};

void f(list<double>& v, int x){
	list<double>::iterator p = sample::find_if(v.begin(), v.end(), Larger_than(31));
	if(p != v.end()) { /* 31よりも大きい値が検出された */ }

	list<double>::iterator q = sample::find_if(v.begin(), v.end(), Larger_than(x));
	if(q != v.end()) { /* xよりも大きい値が検出された */ }
}

int main(){
	list<double> ld(20, 5);
	f(ld, 10);
}