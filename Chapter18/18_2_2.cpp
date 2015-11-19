#include <iostream>
using namespace std;

class vector{
public:
	vector(int s);					// コンストラクタ
	vector(const vector& arg);		// コピーコンストラクタ	
	~vector() { delete[] elem; }	// デストラクタ

	vector& operator=(const vector& a);	// コピー代入

	int size() { return sz; }

	double get(int n) const { return elem[n]; }	// 読み取りアクセス
	void set(int n, double v) { elem[n] = v; }	// 書き込みアクセス 

private:
	int sz;			// サイズ
	double* elem;	// 要素へのポインタ
	void copy(const vector& arg);	// argの要素を*elemにコピーする
};

// コンストラクタ
vector::vector(int s) 
	: sz(s), elem(new double[s]){
	for(int i = 0; i < s; ++i) 
		elem[i] = 0;	// 要素を初期化する
}

// コピーコンストラクタ	
// 要素を割り当てた後、それらをコピーにより初期化する
vector::vector(const vector& arg)
	: sz(arg.sz), elem(new double[arg.sz]){
	copy(arg);
}

// コピー代入
vector& vector::operator=(const vector& a){
	double* p = new double[a.sz];	// 新しい領域を割り当てる
	for(int i = 0; i < a.sz; ++i)
		p[i] = a.elem[i];			// 要素をコピーする
	delete[] elem;					// 古い領域を開放する
	elem = p;						// ここでelemをリセットする
	sz = a.sz;
	return *this;					// 自己参照を返す
}

// [0:arg.sz-1]の要素をコピーする
void vector::copy(const vector& arg){
	for(int i = 0; i < arg.sz; ++i)
		elem[i] = arg.elem[i];
}

void f(){
	vector v(3);
	v.set(2, 2.2);

	vector v2 = v;
	v.set(1, 99);
	v2.set(0, 88);

	cout << v.get(0) << ' ' << v2.get(1) << endl;

	v2 = v;
 
	cout << v.get(0) << ' ' << v2.get(1) << endl;
}

int main(){
	f();
}