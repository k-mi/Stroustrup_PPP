#include <memory>		// auto_ptr
using namespace std;

template<class T, class A = allocator<T> > class vector{
public:
	void reserve(int newalloc);

private:
	A alloc;	// アロケータ

	T* elem;	// 割り当ての開始
	int sz;		// 要素の数
	int space;	// 割り当てた領域の量
};

// 要素の数を変更する
template<class T, class A> void vector<T, A>::reserve(int newalloc){
	if(newalloc <= space) return;				// 割り当てを減らすことはない
	auto_ptr<T*> p = alloc.allocate(newalloc);	// 新しい領域を割り当てる
	for(int i = 0; i < sz; ++i)					// コピー
		alloc.construct(p + i, elem[i]);
	for(int i = 0; i < sz; ++i)					// 削除
		alloc.destroy(&elem[i]);					
	alloc.deallocate(elem, space);				// 古い領域の割り当てを解除する
	space = newalloc;
	elem = p.release();							// 通常のポインタとして渡す
}