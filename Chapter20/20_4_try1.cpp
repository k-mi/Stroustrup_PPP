#include <iostream>
#include <memory>	// alloc
#include <stdexcept>
using namespace std;

// push_front()を用意したvector
template<class T, class A = allocator<T> > class vector{
/*
	不変条件:
		0 <= n < szの場合、elem[n]は要素n
		sz <= space
		sz < spaceの場合、elem[sz-1]の後に(space - sz)個のT分の領域がある
*/

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

	int size() { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T());	// 拡大
	void push_back(const T& val);
	void push_front(const T& val);
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

// vectorのサイズを1つ増やす: ただし、要素の先頭に加える
// push_backとは異なり、要素を確保しない場合もsz分だけ移動させる必要がある
template<class T, class A> void vector<T, A>::push_front(const T& val){
	if(space == 0){
		reserve(8);								// 最初は要素8つ分の領域を確保する
		alloc.construct(&elem[0], val);			// 先頭にvalを追加
	}			
	else if(sz + 1 > space){					// 領域が足りない場合
		T* p = alloc.allocate(2 * space);		// 新しい領域を割り当てる（元の2倍）
		for(int i = 0; i < sz; ++i)				// 1つ後にずらしてコピー（新しいオブジェクトを作成）
			alloc.construct(&p[i+1], elem[i]);
		alloc.construct(&p[0], val);			// 先頭にvalを追加
		for(int i = 0; i < sz; ++i)				// 削除
			alloc.destroy(&elem[i]);					
		alloc.deallocate(elem, space);			// 古い領域の割り当てを解除する
		elem = p;
		space = 2 * space;
	}
	else{										// 領域が足りている場合
		alloc.construct(&elem[sz], elem[sz-1]);	// オブジェクトを後に1つ作成する
		for(int i = sz-1; i > 0; --i) 			// 各要素の値をを1つずつ後へずらす
			elem[i] = elem[i-1];				
		elem[0] = val;							// 最初に要素にvalを代入する
	}
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
	v1.push_front(2);
	v1.push_front(1);
	v1.push_front(0);
	v1.push_back(8);
	print_some(v1);

	vector<int> v2 = v1;
	v2.resize(10, 28);
	v2.push_front(-1);
	print_some(v2);

	vector<int> v3;
	v3.push_front(1);
	v3.push_back(2);
	v3.push_front(0);
	print_some(v3);
}