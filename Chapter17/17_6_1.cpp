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

int main(){
	vector v(5);
	for(int i = 0; i < v.size(); ++i){
		v.set(i, 1.1 * i);
		cout << "v[" << i << "] == " << v.get(i) << endl;
	}
}