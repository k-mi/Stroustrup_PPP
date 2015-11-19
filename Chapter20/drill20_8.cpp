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

// GCC5.2でfindがコンパイルエラーとなるため、こちらを使用
template< class InputIt, class T >
InputIt find2(InputIt first, InputIt last, const T& value){
	while(first != last){
		if(*first == value) return first;
		++first;
	}
	return last;
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

	// 7
	copy2(array, array + size(array), vi.begin());	// 配列→vector
	copy2(li.begin(), li.end(), array);				// list→配列

	print(array, array + size(array));
	print(vi.begin(), vi.end());
	print(li.begin(), li.end());

	// 8
	auto it1 = find2(vi.begin(), vi.end(), 3);
	if(it1 != vi.end()) cout << it1 - vi.begin() << endl; 

	auto it2 = find2(li.begin(), li.end(), 27);
	if(it2 != li.end()){
		int position = 0;
		for(auto it = li.begin(); it != it2; ++it)
			position++;
		cout << position << endl;
	}
}