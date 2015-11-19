#include <iostream>
using namespace std;

// 非常に単純なdouble型のvector
class vector{
public:
	vector(int s) : sz(s), elem(new double[s]){	// コンストラクタ
		for(int i = 0; i < s; ++i) elem[i] = 0;	// 要素を初期化する
	}
	~vector() { delete[] elem; }	// デストラクタ

	int size() { return sz; }

	double get(int n) const { return elem[n]; }	// 読み取りアクセス
	void set(int n, double v) { elem[n] = v; }	// 書き込みアクセス 

private:
	int sz;			// サイズ
	double* elem;	// 要素へのポインタ
};

vector* f(int s){
	vector* p = new vector(s);	// ヒープにvectorを割り当てる
	// *pにデータを設定する
	return p;
}

void ff(){
	vector* q = f(4);
	// *pを使用する
	delete q;	// ヒープへvectorを開放する
}

int main(){
	ff();
}