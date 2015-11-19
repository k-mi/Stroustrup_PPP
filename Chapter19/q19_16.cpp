#include <iostream>
#include <stdexcept>	
using namespace std;

template<class T, class A = allocator<T> > struct Data{
	A alloc;	// アロケータ—を使って要素のメモリを処理する

	int sz;		// サイズ
	T* elem;	// 要素へのポインタ（またはnullptr）
	int space;	// 要素の数 + 空き領域
};

// Tの本物にそっくりのvector（allocatorバージョン）
template<class T, class A = allocator<T> > class vector{
/*
	不変条件:
		0 <= n < pointer->szの場合、pointer->elem[n]は要素n
		pointer->sz <= pointer->space
		pointer->sz < pointer->spaceの場合、pointer->elem[pointer->sz-1]の後に(pointer->space - pointer->sz)個のT分の領域がある
*/

public:
	vector() 								// デフォルトコンストラクタ
		: pointer(new Data<T, A>) { pointer->sz = 0; pointer->elem = nullptr; pointer->space = 0; }	
	explicit vector(int s, T val = T());	// コンストラクタ
	vector(const vector& arg);				// コピーコンストラクタ	
	vector& operator=(const vector& a);		// コピー代入

	~vector();								// デストラクタ	

	// アクセス
	T& at(int n);											// チェック付きのアクセス（非const vector用）
	const T& at(int n) const;								// チェック付きのアクセス（const vector用）
	T& operator[](int n) { return pointer->elem[n]; }				// チェックなしのアクセス（非const vector用）
	const T& operator[](int n) const { return pointer->elem[n]; }	// チェックなしのアクセス（const vector用）

	int size() { return pointer->sz; }
	int capacity() const { return pointer->space; }

	void resize(int newsize, T val = T());	// 拡大
	void push_back(const T& val);
	void reserve(int newalloc);

private:
	Data<T, A>* pointer;
};

// コンストラクタ
template<class T, class A> vector<T, A>::vector(int s, T val) 
	: pointer(new Data<T, A>){
	pointer->sz = s;
	pointer->elem = pointer->alloc.allocate(s);
	pointer->space = s;
	for(int i = 0; i < s; ++i) 
		pointer->alloc.construct(&(pointer->elem)[i], val);	// 初期化
}

// コピーコンストラクタ	
// 要素を割り当てた後、それらをコピーにより初期化する
template<class T, class A> vector<T, A>::vector(const vector& arg)
	: pointer(new Data<T, A>){
	pointer->sz = arg.pointer->sz;
	pointer->elem = pointer->alloc.allocate(arg.pointer->sz);
	pointer->space = arg.pointer->sz;
	for(int i = 0; i < pointer->sz; ++i)			// コピー
		pointer->alloc.construct(&(pointer->elem)[i], arg[i]);
}

// コピー代入
// コピーコンストラクタに似ているが、古い要素を処理しなければならない
template<class T, class A> vector<T, A>& vector<T, A>::operator=(const vector& a){
	if(this == &a) return *this;							// 自己代入なので、作業は必要ない

	if(a.pointer->sz <= pointer->space){					// 領域は十分なので、新しい割り当ては必要ない
		for(int i = 0; i < pointer->sz; ++i)				// コピー
			pointer->alloc.construct(&(pointer->elem)[i], a[i]);
		for(int i = a.pointer->sz; i < pointer->space; ++i)	// 削除
			pointer->alloc.destroy(&(pointer->elem)[i]);
		pointer->sz = pointer->space = a.pointer->sz;
		return *this;
	}

	T* p = pointer->alloc.allocate(a.pointer->sz);			// 新しい領域を割り当てる
	for(int i = 0; i < a.pointer->sz; ++i)				// コピー
		pointer->alloc.construct(&p[i], a[i]);
	for(int i = 0; i < pointer->sz; ++i)				// 削除
		pointer->alloc.destroy(&p[i]);					
	pointer->alloc.deallocate(pointer->elem, pointer->space);	// 古い領域の割り当てを解除する
	pointer->space = pointer->sz = a.pointer->sz;		// 新しいサイズを設定する
	pointer->elem = p;									// 新しい要素を設定する

	return *this;										// 自己参照を返す
}

// デストラクタ
template<class T, class A> vector<T, A>::~vector(){
	for(int i = 0; i < pointer->sz; ++i)
		pointer->alloc.destroy(&(pointer->elem)[i]);	// 削除
	pointer->alloc.deallocate(pointer->elem, pointer->space); // 割り当てを解除する 
}

// チェック付きのアクセス（非const vector用）
template<class T, class A> T& vector<T, A>::at(int n){
	if(n < 0 || pointer->sz <= n) throw out_of_range(to_string(n));
	return pointer->elem[n];
}

// チェック付きのアクセス（非const vector用）
template<class T, class A> const T& vector<T, A>::at(int n) const{
	if(n < 0 || pointer->sz <= n) throw out_of_range(to_string(n));
	return pointer->elem[n];
}

// 要素の数を変更する
template<class T, class A> void vector<T, A>::reserve(int newalloc){
	if(newalloc <= pointer->space) return;				// 割り当てを減らすことはない
	T* p = pointer->alloc.allocate(newalloc);					// 新しい領域を割り当てる
	for(int i = 0; i < pointer->sz; ++i)				// コピー
		pointer->alloc.construct(&p[i], pointer->elem[i]);
	for(int i = 0; i < pointer->sz; ++i)				// 削除
		pointer->alloc.destroy(&(pointer->elem)[i]);					
	pointer->alloc.deallocate(pointer->elem, pointer->space);	// 古い領域の割り当てを解除する
	pointer->elem = p;
	pointer->space = newalloc;
}

// vectorのサイズを1つ増やす: 新しい要素でdを初期化する
template<class T, class A> void vector<T, A>::push_back(const T& val){
	if(pointer->space == 0) reserve(8);									// 最初は要素8つ分の領域を確保する
	else if(pointer->sz == pointer->space) reserve(2 * pointer->space);	// さらに領域を割り当てる
	pointer->alloc.construct(&(pointer->elem)[pointer->sz], val);				// valを最後に追加する
	++pointer->sz;														// サイズを増やす（pointer->szは要素の数）
}

// vectorにnewsize個の要素を持たせる
// 新しい要素をそれぞれデフォルト値または引数で指定した値で初期化する
template<class T, class A> void vector<T, A>::resize(int newsize, T val){
	reserve(newsize);
	for(int i = pointer->sz; i < newsize; ++i)	// 生成
		pointer->alloc.construct(&(pointer->elem)[i], val);
	for(int i = newsize; i < pointer->sz; ++i)	// 削除
		pointer->alloc.destroy(&(pointer->elem)[i]);
	pointer->sz = newsize;
}

// vector<int>型専用
void print_some(vector<int>& v){
	int i = -1;
	while(cin >> i && i != -1){
		try{
			cout << "v[" << i << "]==" << v.at(i) << "\n"; 
		}
		catch(out_of_range){
			cout << "bad index: " << i << "\n";
		}
	}
}

int main(){
	cout << "vector<int>: " << sizeof(vector<int>) << endl;
	cout << "int*: " << sizeof(int*) << endl;

	// テスト
	vector<int> v1(5, 31);
	print_some(v1);

	vector<int> v2 = v1;
	v2.resize(10, 28);
	print_some(v2);

	v2 = v1;
	print_some(v2);
}