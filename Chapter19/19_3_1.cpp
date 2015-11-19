#include <iostream>
using namespace std;

// Tの本物にそっくりのvector
template<class T> class vector{
/*
	不変条件:
		0 <= n < szの場合、elem[n]は要素n
		sz <= space
		sz < spaceの場合、elem[sz-1]の後に(space - sz)個のT分の領域がある
*/

public:
	vector() 								// デフォルトコンストラクタ
		: sz(0), elem(nullptr), space(0) { }	
	explicit vector(int s, T def = T());	// コンストラクタ
	vector(const vector& arg);				// コピーコンストラクタ	
	vector& operator=(const vector& a);		// コピー代入

	~vector() { delete[] elem; }			// デストラクタ

	// アクセス
	T& operator[](int n) { return elem[n]; }				// 非const vector用（参照を返す）
	const T& operator[](int n) const { return elem[n]; }	// const vector用（const参照を返す）

	int size() { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T def = T());	// 拡大
	void push_back(const T& d);
	void reserve(int newalloc);

private:
	int sz;		// サイズ
	T* elem;	// 要素へのポインタ（またはnullptr）
	int space;	// 要素の数 + 空き領域

	void copy(const vector& arg);	// argの要素を*elemにコピーする
};

// コンストラクタ
template<class T> vector<T>::vector(int s, T def) 
	: sz(s), elem(new T[s]), space(s){
	for(int i = 0; i < s; ++i) 
		elem[i] = def;	// 要素を初期化する
}

// コピーコンストラクタ	
// 要素を割り当てた後、それらをコピーにより初期化する
template<class T> vector<T>::vector(const vector& arg)
	: sz(arg.sz), elem(new T[arg.sz]), space(arg.sz){
	copy(arg);
}

// コピー代入
// コピーコンストラクタに似ているが、古い要素を処理しなければならない
template<class T> vector<T>& vector<T>::operator=(const vector& a){
	if(this == &a) return *this;	// 自己代入なので、作業は必要ない

	if(a.sz <= space){				// 領域は十分なので、新しい割り当ては必要ない
		copy(a);		
		sz = a.sz;
		return *this;
	}

	T* p = new T[a.sz];				// 新しい領域を割り当てる
	for(int i = 0; i < a.sz; ++i)	// 要素をコピーする
		p[i] = a.elem[i];					
	delete[] elem;					// 古い領域の割り当てを解除する
	space = sz = a.sz;				// 新しいサイズを設定する
	elem = p;						// 新しい要素を設定する
	return *this;					// 自己参照を返す
}

// [0:arg.sz-1]の要素をコピーする
template<class T> void vector<T>::copy(const vector& arg){
	for(int i = 0; i < arg.sz; ++i)
		elem[i] = arg.elem[i];
}

// 要素の数を変更する
template<class T> void vector<T>::reserve(int newalloc){
	if(newalloc <= space) return;		// 割り当てを減らすことはない
	T* p = new T[newalloc];	// 新しい領域を割り当てる
	for(int i = 0; i < sz; ++i)			// 古い領域をコピーする
		p[i] = elem[i];					
	delete[] elem;						// 古い領域の割り当てを解除する
	elem = p;
	space = newalloc;
}

// vectorにnewsize個の要素を持たせる
// 新しい要素をそれぞれデフォルト値または引数で指定した値で初期化する
template<class T> void vector<T>::resize(int newsize, T def){
	reserve(newsize);
	for(int i = sz; i < newsize; ++i)	// 新しい要素を初期化する
		elem[i] = def;
	sz = newsize;
}

// vectorのサイズを1つ増やす: 新しい要素でdを初期化する
template<class T> void vector<T>::push_back(const T& d){
	if(space == 0) reserve(8);					// 最初は要素8つ分の領域を確保する
	else if(sz == space) reserve(2 * space);	// さらに領域を割り当てる
	elem[sz] = d;								// dを最後に追加する
	++sz;										// サイズを増やす（szは要素の数）
}

int main(){
	vector<float> vd1(20, 3.14);
	cout << vd1[5] << endl;
	vd1[10] = 1.4142;
	cout << vd1[10] << endl;

	vector<float> vd2(vd1);
	cout << vd2[5] << endl;
	cout << vd2[10] << endl;
	vd2[5] = 12345678;
	cout << vd2[5] << endl;

	vd2.resize(300, 31.31);
	cout << vd2[20] << endl;
	vd2.push_back(62.62);
	cout << vd2[300] << endl;

	vd1 = vd2;
	cout << vd1[299] << endl;
	cout << vd1[300] << endl;
	cout << vd1[5] << endl;
}