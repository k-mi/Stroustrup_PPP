#include <cstdlib>	// malloc, free
#include <new>		// bad_alloc	

template<class T> class allocator{
public:
	T* allocate(int n);
	void deallocate(T* p, int n);

	void construct(T* p, const T& v);
	void destroy(T* p);
};

// T型のオブジェクトn個の領域を割り当てる
template<class T> T* allocator<T>::allocate(int n){
	T* p = reinterpret_cast<T*>(malloc(n * sizeof(T)));
	if(p == nullptr) throw bad_alloc();
	return p;
}

// pで始まるT型のオブジェクトn個の領域を開放する
template<class T> void allocator<T>::deallocate(T* p, int n){
	free(p);
}

// pにT型のオブジェクトを作成し、値vで初期化する
template<class T> void allocator<T>::construct(T* p, const T& v){
	memcpy(p, &v, sizeof(T));
	// new(p) T(); 	// <new>ヘッダの placement newでもOK
}

// pにポイントされるT型のオブジェクトを削除する
template<class T> void allocator<T>::destroy(T* p){
	p->~T();
}