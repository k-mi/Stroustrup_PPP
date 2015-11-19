#include <iostream>
#include <ctime>	// clock_t, clock
#include <cstdlib>	// exit
#include <vector>
using namespace std;

// 500バイトのオブジェクト
struct Obj500{
	char data[500];
};

int randint(int n){
	return rand() % n;
}

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

	int r = randint(N);
	while(!freelist[r]){
		r = randint(N);
	}
	freelist[r] = false;
	return &elements[r];

/*
	for(int i = 0; i < N; ++i){
		if(freelist[i]){
			freelist[i] = false;
			return &elements[i];
		}
	}
*/
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

template<int N> class Stack{	// Nバイトのスタック
public:
	Stack();				// Nバイトのスタックを作成する
	~Stack();				// Nバイトのスタックを削除する

	void* get(int n);		// スタックからnバイトを割り当てる（空き領域がない場合は0を返す）

	void free();			// get()から返された最後の値をスタックに戻す

	int available() const { return N - int(front - space); }	// 利用可能なバイト数

private:
	char* space;			// char[N]のための領域
	char* front;			// スタックの先頭ポインタ
	vector<int> el_size;	// 各要素のサイズを保持
};

template<int N> Stack<N>::Stack(){
	space = new char[N];
	front = space;
}

template<int N> Stack<N>::~Stack(){
	delete[] space;
}

template<int N> void* Stack<N>::get(int n){
	if(available() < 0) return nullptr;	// 領域が足りない場合

	char* tmp = front;
	front += n;
	el_size.push_back(n);
	return tmp;
}

template<int N> void Stack<N>::free(){
	if(space == front) return;			// スタックに何も入っていない場合

	front -= el_size[el_size.size() - 1];
	el_size.pop_back();
}

double freestore_allocate(vector<char*>& vc){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	for(auto x : vc)
		x = new char[randint(1000) + 1];

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double freestore_deallocate1(vector<char*>& vc){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	// 割り当てと逆の順序で解放
	for(auto it = vc.rbegin(); it != vc.rend(); ++it)
		delete[] *it;

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double freestore_deallocate2(vector<char*>& vc){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	// ランダムな順序で解放
	int count = 0;
	while(count < vc.size()){
		int r = randint(vc.size());
		if(vc[r] != nullptr){
			delete[] vc[r];
			vc[r] = nullptr;
			count++;
		}
	}

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double pool_allocate(vector<Obj500*>& vo, Pool<Obj500, 10000>& pool){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	Obj500* tmp;	

	while(true){
		tmp = pool.get();	// 取得
		if(tmp == nullptr) break;

		vo.push_back(tmp);
	}

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double pool_deallocate(vector<Obj500*>& vo, Pool<Obj500, 10000>& pool){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	for(auto x : vo)
		pool.free(x);		// 返還

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double stack_allocate(vector<char*>& vc, Stack<10000 * 1000>& stack){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	for(int i = 0; i < 10000; ++i){
		int r = randint(1000) + 1;
		void* p = stack.get(r);	
		if(p != nullptr)
			vc.push_back(static_cast<char*>(p));
	}

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;
}

double stack_deallocate(vector<char*>& vc, Stack<10000 * 1000>& stack){
	clock_t t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	// 逆の順序で解放
	for(int i = 0; i < vc.size(); ++i)
		stack.free();		

	clock_t t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);

	return double(t2 - t1) / CLOCKS_PER_SEC * 1000;	
}

int main(){
	vector<char*> vc1(10000), vc2(10000);
	cout << "new(free-store): " << freestore_allocate(vc1) << "[ms]" << endl;
	cout << "reverse delete(free-store): " << freestore_deallocate1(vc1) << "[ms]" << endl;
	cout << "new(free-store): " << freestore_allocate(vc2) << "[ms]" << endl;
	cout << "random delete(free-store): " << freestore_deallocate1(vc2) << "[ms]" << endl << endl;

	Pool<Obj500, 10000> pool;
	vector<Obj500*> vo(10000);
	cout << "allocate(pool): " << pool_allocate(vo, pool) << "[ms]" << endl;
	cout << "deallocate(pool): " << pool_deallocate(vo, pool) << "[ms]" << endl << endl;

	Stack<10000 * 1000> stack;
	vector<char*> vc3;
	cout << "allocate(stack): " << stack_allocate(vc3, stack) << "[ms]" << endl;
	cout << "reverse deallocate(stack): " << stack_deallocate(vc3, stack) << "[ms]" << endl << endl;
}