#include <iostream>
#include <vector>
#include <stdexcept>	// runtime_error
using namespace std;

template<class T, int N> class Pool{
public:
	Pool();					// プールを作成する
	~Pool();				// プールを削除する

	T* get();				// プールからTを取得する（フリーのTがない場合は0を返す）
	void free(T*); 			// getで取得したTをプールに戻す

	int available() const { return left; }	// フリーのTの数

private:
	T* elements;			// T[N]のための領域
	bool* freelist;			// フリーオブジェクトのリスト（空いている要素はtrue）
	int left;				// フリーのTの数
};

template<class T, int N> Pool<T, N>::Pool() : left(N){
	if(N <= 0) throw runtime_error("no elements");

	elements = new T[N];
	freelist = new bool[N];
	for(int i = 0; i < N; ++i) 
		freelist[i] = true;
}

template<class T, int N> Pool<T, N>::~Pool(){
	delete[] elements;
	delete[] freelist;
}

template<class T, int N> T* Pool<T, N>::get(){
	if(left == 0) return nullptr;
	--left;

	for(int i = 0; i < N; ++i){
		if(freelist[i]){
			freelist[i] = false;
			return &elements[i];
		}
	}
}

template<class T, int N> void Pool<T, N>::free(T* p){
	if(p < &elements[0] || &elements[N - 1] < p) return;

	int index = (p - elements);
	freelist[index] = true;
	++left;

/*	
	for(int i = 0; i < N; ++i){
		if(&elements[i] == p){
			freelist[i] = true;
			++left;
			break;
		}
	}
*/
}

int main(){
	Pool<int, 1000> pool;
	
	int* tmp;	
	vector<int*> vip;

	while(true){
		tmp = pool.get();	// 取得
		if(tmp == nullptr) break;

		*tmp = 123456;		// 適当な値を代入
		vip.push_back(tmp);
	}

	cout << "available: " << pool.available() << endl;
	cout << "vip size: " << vip.size() << endl;

	for(auto x : vip)
		pool.free(x);		// 返還

	cout << "available: " << pool.available() << endl;
}