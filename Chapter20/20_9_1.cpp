#include <iostream>
using namespace std;

// 規格のarrayとまったく同じではない
template<class T, int N> struct array{
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef unsigned int size_type;		// 添え字の型

	T elems[N];

	// 明示的なコンストラクション、コピー、デストラクションは必要ない

	iterator begin() { return elems; }
	const_iterator begin() const { return elems; }
	iterator end() { return elems + N; }
	const_iterator end() const { return elems + N; }

	size_type size() const { return N; }

	T& operator[](int n) { return elems[n]; }
	const T& operator[](int n) const { return elems[n]; }

	const T& at(int n) const;	// 範囲チェック付きアクセス
	T& at(int n);

	T* data() { return elems; }
	const T* data() const { return elems; } 
};

// 範囲チェック付きアクセス
template<class T, int N> const T& array<T, N>::at(int n) const{
	if(0 > n || n >= N) throw out_of_range("index: " + to_string(n));
	return elems[n];
}

template<class T, int N> T& array<T, N>::at(int n){
	if(0 > n || n >= N) throw out_of_range("index: " + to_string(n));
	return elems[n];	
}

// 最も大きな値を持つ[first:last)の範囲内の要素へのイテレータを返す
template<class Iterator> 
Iterator high(Iterator first, Iterator last){
	Iterator high = first;
	for(Iterator p = first; p != last; ++p)
		if(*high < *p) high = p;
	return high;
}

void f(){
	array<double, 6> a = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5 };
	array<double, 6>::iterator p = high(a.begin(), a.end());
	cout << "the highest value was " << *p << endl;
}

int main(){
	f();
}