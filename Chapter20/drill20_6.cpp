#include <iostream>
#include <vector>
#include <list>
using namespace std;

#define size(array) (sizeof(array) / sizeof(*array))	// 配列の要素数マクロ

// [first,end)をcoutで表示する
template<class Iter> void print(Iter first, Iter end){
	if(first == end) return;
	for(Iter it = first; it != end; ++it)
		cout << *it << ' ';
	cout << endl;
}

// [first,end)にnを加える
template<class Iter, class T> void add(Iter first, Iter end, T n){
	if(first == end) return;
	for(Iter it = first; it != end; ++it)
		*it += n;
}

// 6
// [f1,e1)を[f2,f2+(e1-f1))にコピーし、f2+(e1-f1))を返す
// 名前をcopy2に変更
template<class Iter1, class Iter2> Iter2 copy2(Iter1 f1, Iter1 e1, Iter2 f2){
	if(f1 == e1) return f2;
	for(Iter1 it = f1; it != e1; ++it){
		*f2 = *it;
		++f2;
	}
	return f2;
}

int main(){
	// -std=c++11が必要
	int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };		// 1
	vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };	// 2
	list<int> li = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };	// 3

	// 4
	int array2[size(array)];
	for(int i = 0; i < size(array2); ++i)
		array2[i] = array[i];
	vector<int> vi2 = vi;
	list<int> li2 = li;

	// 5
	add(array, array + size(array), 2);
	add(vi.begin(), vi.end(), 3);
	add(li.begin(), li.end(), 5);

	// 6 test
	copy2(array, array + size(array), array2);
	copy2(vi.begin(), vi.end(), vi2.begin());
	copy2(li.begin(), li.end(), li2.begin());

	print(array2, array2 + size(array2));
	print(vi2.begin(), vi2.end());
	print(li2.begin(), li2.end());
}