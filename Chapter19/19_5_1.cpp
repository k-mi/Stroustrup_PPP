#include <memory>		// uninitidalized_copy
#include <algorithm>	// swap
using namespace std;

template<class T, class A> struct vector_base{
	A alloc;	// アロケータ
	T* elem;	// 割り当ての開始
	int sz;		// 要素の数
	int space;	// 割り当てた領域の量

	vector_base(const A& a, int n)
		: alloc(a), elem(alloc.allocate(n)), sz(n), space(n) { }
	~vector_base() { alloc.deallocate(elem, space); }		
};

template<class T, class A = allocator<T> > class vector : private vector_base<T, A>{
public:
	void reserve(int newalloc);
};

template<class T, class A> void vector<T, A>::reserve(int newalloc){
	if(newalloc <= space) return;			// 割り当てを減らすことはない
	vector_base<T, A> b(alloc, newalloc);	// 新しい領域を割り当てる
	// 各引数は、コピー先の最初のポインタ、最後の次のポインタ、コピー元の最初のポインタ
	uninitialized_copy(b.elem, &b,elem[this->sz], this->elem);	// コピー
	for(int i = 0; i < this->sz; ++i)		// 削除
		this->alloc.destroy(&this->elem[i]);					
	swap< <vector_base<T, A> >(*this, b);	// 表現を交換する
}