#include <iostream>
#include <vector>

template<class T> class auto_ptr{
public:
	explicit auto_ptr(T* p) 
		: pointer(p), is_release(false) { }			// コンストラクタ

	~auto_ptr() {									// デストラクタ
		std::cout << "auto_ptr::~auto_ptr()" << std::endl;
		
		if(!is_release) delete pointer; 
	}	

	T* operator->() { return pointer; }
	T& operator*() { return *pointer; }

	T* release() { is_release = true; return pointer; }

private:
	bool is_release;
	T* pointer;
};

std::vector<int>* make_vec(){
	auto_ptr< std::vector<int> > p(new std::vector<int>);
	
	p->push_back(28);
	std::cout << (*p).at(0) << std::endl; 
	
	p->at(1);	// 領域外参照でexceptionを発生させる

	return p.release();
}

int main(){
	try{
		std::vector<int>* p = make_vec();
		std::cout << p->at(0) << std::endl;		
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}