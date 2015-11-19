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

	print(array, array + size(array));
	print(vi.begin(), vi.end());
	print(li.begin(), li.end());
}