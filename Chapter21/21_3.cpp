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

double v_val;	// larger_than_v()がその引数と比較する値
bool larger_than_v(double x) { return x > v_val; }

void f(list<double>& v, int x){
	v_val = 31;	// larger_than_xの次の呼び出しに対してv_valを31に設定する
	list<double>::iterator p = sample::find_if(v.begin(), v.end(), larger_than_v);
	if(p != v.end()) { /* 31よりも大きい値が検出された */ }

	v_val = x;	// larger_than_xの次の呼び出しに対してv_valをxに設定する
	list<double>::iterator q = sample::find_if(v.begin(), v.end(), larger_than_v);
	if(q != v.end()) { /* xよりも大きい値が検出された */ }

	// ...
}

int main(){
	list<double> ld(20, 5);
	f(ld, 10);
}