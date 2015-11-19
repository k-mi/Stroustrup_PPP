#include <iostream>
#include <memory>	// alloc
#include <stdexcept>
using namespace std;

// begin()およびend()を追加したvector
template<class T, class A = allocator<T> > class vector{

public:
	vector() 								// デフォルトコンストラクタ
		: sz(0), elem(nullptr), space(0) { }	
	explicit vector(int s, T val = T());	// コンストラクタ
	vector(const vector& arg);				// コピーコンストラクタ	
	vector& operator=(const vector& a);		// コピー代入

	~vector();								// デストラクタ	

	// アクセス
	T& at(int n);											// チェック付きのアクセス（非const vector用）
	const T& at(int n) const;								// チェック付きのアクセス（const vector用）
	T& operator[](int n) { return elem[n]; }				// チェックなしのアクセス（非const vector用）
	const T& operator[](int n) const { return elem[n]; }	// チェックなしのアクセス（const vector用）

	typedef unsigned long size_type;
	typedef T value_type;
	typedef T* iterator;
	typedef const T* const_iterator;

	iterator begin() { return &elem[0]; };
	const_iterator begin() const { return &elem[0]; };
	iterator end() { return &elem[sz]; }
	const_iterator end() const { return &elem[sz]; }

	size_type size() { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T());	// 拡大
	void push_back(const T& val);
	void reserve(int newalloc);

private:
	A alloc;	// アロケータ—を使って要素のメモリを処理する

	int sz;		// サイズ
	T* elem;	// 要素へのポインタ（またはnullptr）
	int space;	// 要素の数 + 空き領域
};

// コンストラクタ
template<class T, class A> vector<T, A>::vector(int s, T val) 
	: sz(s), elem(alloc.allocate(s)), space(s){
	for(int i = 0; i < s; ++i) 
		alloc.construct(&elem[i], val);	// 初期化
}

// コピーコンストラクタ	
// 要素を割り当てた後、それらをコピーにより初期化する
template<class T, class A> vector<T, A>::vector(const vector& arg)
	: sz(arg.sz), elem(alloc.allocate(arg.sz)), space(arg.sz){
	for(int i = 0; i < sz; ++i)			// コピー
		alloc.construct(&elem[i], arg[i]);
}

// コピー代入
// コピーコンストラクタに似ているが、古い要素を処理しなければならない
template<class T, class A> vector<T, A>& vector<T, A>::operator=(const vector& a){
	if(this == &a) return *this;			// 自己代入なので、作業は必要ない

	if(a.sz <= space){						// 領域は十分なので、新しい割り当ては必要ない
		for(int i = 0; i < sz; ++i)			// コピー
			alloc.construct(&elem[i], a[i]);
		for(int i = a.sz; i < space; ++i)	// 削除
			alloc.destroy(&elem[i]);
		sz = space = a.sz;
		return *this;
	}

	T* p = alloc.allocate(a.sz);		// 新しい領域を割り当てる
	for(int i = 0; i < a.sz; ++i)		// コピー
		alloc.construct(&p[i], a[i]);
	for(int i = 0; i < sz; ++i)			// 削除
		alloc.destroy(&p[i]);					
	alloc.deallocate(elem, space);		// 古い領域の割り当てを解除する
	space = sz = a.sz;					// 新しいサイズを設定する
	elem = p;							// 新しい要素を設定する

	return *this;					// 自己参照を返す
}

// デストラクタ
template<class T, class A> vector<T, A>::~vector(){
	for(int i = 0; i < sz; ++i)
		alloc.destroy(&elem[i]);	// 削除
	alloc.deallocate(elem, space); 	// 割り当てを解除する 
}

// チェック付きのアクセス（非const vector用）
template<class T, class A> T& vector<T, A>::at(int n){
	if(n < 0 || sz <= n) throw out_of_range(to_string(n));
	return elem[n];
}

// チェック付きのアクセス（非const vector用）
template<class T, class A> const T& vector<T, A>::at(int n) const{
	if(n < 0 || sz <= n) throw out_of_range(to_string(n));
	return elem[n];
}

// 要素の数を変更する
template<class T, class A> void vector<T, A>::reserve(int newalloc){
	if(newalloc <= space) return;		// 割り当てを減らすことはない
	T* p = alloc.allocate(newalloc);	// 新しい領域を割り当てる
	for(int i = 0; i < sz; ++i)			// コピー
		alloc.construct(&p[i], elem[i]);
	for(int i = 0; i < sz; ++i)			// 削除
		alloc.destroy(&elem[i]);					
	alloc.deallocate(elem, space);		// 古い領域の割り当てを解除する
	elem = p;
	space = newalloc;
}

// vectorのサイズを1つ増やす: 新しい要素でdを初期化する
template<class T, class A> void vector<T, A>::push_back(const T& val){
	if(space == 0) reserve(8);					// 最初は要素8つ分の領域を確保する
	else if(sz == space) reserve(2 * space);	// さらに領域を割り当てる
	alloc.construct(&elem[sz], val);			// valを最後に追加する
	++sz;										// サイズを増やす（szは要素の数）
}

// vectorにnewsize個の要素を持たせる
// 新しい要素をそれぞれデフォルト値または引数で指定した値で初期化する
template<class T, class A> void vector<T, A>::resize(int newsize, T val){
	reserve(newsize);
	for(int i = sz; i < newsize; ++i)	// 生成
		alloc.construct(&elem[i], val);
	for(int i = newsize; i < sz; ++i)	// 削除
		alloc.destroy(&elem[i]);
	sz = newsize;
}

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
	vector<int> v1(5, 31);
	print_some(v1);

	vector<int> v2 = v1;
	v2.resize(10, 28);
	print_some(v2);

	v2 = v1;
	print_some(v2);
}