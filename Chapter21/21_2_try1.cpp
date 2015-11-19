#include <iostream>
#include <vector>
using namespace std;

/*
	21.2 TRY THIS

	2:
	for文の初期化式では、イテレータpにfirstをコピーしているため、
	この2つの値は同じであると言える。
	また、firstについてもfind()関数に実引数が渡され、
	この関数内のみのスコープを持つそのコピーであることから、
	置かれた状態もpと同じであると言える。
	したがって、2つは等価であり、pを置き換えること初期化式の削除が可能である。

	3:	
	このforループの終了条件は、for文の継続条件式の否定である「first == last」と
	ネストされたif文の「*first == val」である。
	この2つの条件による戻り値は異なっているが、
	if文の条件に当てはまった場合は、その時のfirstを戻り値できれば良く、
	for文の条件を外れた段階では、firstはlastと同じ値を示すことになるため、
	if文をbreakにし、最後の戻り値をfirstと置き換えることが可能である。

	4:
	if文の条件によって発生する動作は、forループから抜けるだけであるため、
	これの否定をfor文の継続条件式に加えることができる。

	5:
	このfor文を等価なwhile文に置き換えると、望ましいバージョンにとなる。	
*/

// 1: 平凡な方法
template<class In, class T> In find1(In first, In last, const T& val){
	for(In p = first; p != last; ++p)
		if(*p == val) return p;
	return last;
}

// 2:
template<class In, class T> In find2(In first, In last, const T& val){
	for(; first != last; ++first)
		if(*first == val) return first;
	return last;
}

// 3:
template<class In, class T> In find3(In first, In last, const T& val){
	for(; first != last; ++first)
		if(*first == val) break;
	return first;
}

// 4:
template<class In, class T> In find4(In first, In last, const T& val){
	for(; first != last && *first != val; ++first);
	return first;
}

// 5:
template<class In, class T> In find5(In first, In last, const T& val){
	while(first != last && *first != val) ++first;
	return first;
}

int main(){
	vector<int> v(5, 10);
	v[3] = 31;

	cout << (find1(v.begin(), v.end(), 31) != v.end() ? "find" : "unfind") << endl;
	cout << (find2(v.begin(), v.end(), 31) != v.end() ? "find" : "unfind") << endl;
	cout << (find3(v.begin(), v.end(), 31) != v.end() ? "find" : "unfind") << endl;
	cout << (find4(v.begin(), v.end(), 31) != v.end() ? "find" : "unfind") << endl;
	cout << (find5(v.begin(), v.end(), 31) != v.end() ? "find" : "unfind") << endl;
}