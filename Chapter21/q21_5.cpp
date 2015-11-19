#include <iostream>
#include <vector>
using namespace std;

// 関数名をfindからfind2に変更
// 探す範囲の次の要素をポイントする第二引数とは別に、シーケンスの末尾を第三引数として渡す。
template<class InputIt, class T>
InputIt find2(InputIt first, InputIt last, InputIt end, const T& value){
	while(first != last){
		if(*first == value) return first;
		++first;
	}
	return end;
}

// 関数名をcountからcount2に変更
// q21_3と変更なし（見つからない場合は0を返す）。
template<class InputIt, class T> 
int count2(InputIt first, InputIt last, const T& value){
	int cnt = 0;
	while(first != last){
		if(*first == value) ++cnt;
		++first;
	}
	return cnt;
}

int main(){
	vector<double> vd(5, 3.14);
	vd[2] = -3.14;
	vd[4] = 0;

	vector<double>::iterator p = find2(vd.begin(), vd.begin()+3, vd.end(), 5); 
	if(p != vd.end()) cout << *p << endl;	// not execute
	p = find2(vd.begin(), vd.begin()+3, vd.end(), 3.14); 
	if(p != vd.end()) cout << *p << endl;
	p = find2(vd.begin(), vd.begin()+3, vd.end(), 0); 
	if(p != vd.end()) cout << *p << endl;	// not execute

	cout << count2(vd.begin(), vd.end(), 3.14) << endl;		// 3
	cout << count2(vd.begin(), vd.end(), -3.14) << endl;	// 1
	cout << count2(vd.begin(), vd.end(), 0.0) << endl;		// 1
	cout << count2(vd.begin(), vd.end(), 2.5) << endl;		// 0
}