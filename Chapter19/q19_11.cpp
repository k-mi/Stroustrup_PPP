#include <iostream>
#include <vector>
using namespace std;

template<class T> class counted_ptr{
public:
	explicit counted_ptr(const T& p) 	// コンストラクタ
		: pointer(new T(p)), count(new int(1)) { }		
	counted_ptr(counted_ptr& cp)		// コピーコンストラクタ		
		: pointer(cp.pointer), count(cp.count) { (*count)++; }

	~counted_ptr() { 					// デストラクタ
		cout << "count_ptr::~count_ptr()" << endl;

		(*count)--; 
		if(*count == 0){
			delete pointer;
			delete count; 
			cout << "(deleted)" << endl;
		}
	}

	T* operator->() { return pointer; }
	T operator*() { return *pointer; }	

private:
	T* pointer;
	int* count;
};

int main(){
	vector<int> vi;

	counted_ptr< vector<int> > p(vi);
	p->push_back(28);
	cout << (*p).at(0) << endl;

	//counted_ptr< vector<int> > p2(p);
	auto p2 = p;
	p2->push_back(31);
	cout << p2->at(0) << ' ' << p2->at(1) << endl;
}