#include <iostream>
#include <vector>
using namespace std;

// 簡単なテストクラス
struct X{
	int val;

	void out(const string& s, int nv){
		cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}

	X(){ out("X()", 0); val = 0; }						// デフォルトコンストラクタ
	X(int x) { out("X(int)", x); val = x; }
	X(const X& x) { out("X(X&)", x.val); val = x.val; }	// コピーコンストラクタ
	X& operator=(const X& a) {							// コピー代入
		out("X::operator=()", a.val); 
		val = a.val; 
		return *this;
	}
	~X() { out("~X()", 0); }							// デストラクタ
};

X glob(2);	// グローバル変数→コンストラクタ

X copy(X a) { return a; }

X copy2(X a) { X aa = a; return aa; }

X& ref_to(X& a) { return a; }

X* make(int i) { X a(i); return new X(a); }

struct XX { X a; X b; };

int main(){
	cout << endl;
	X loc(4);			// ローカル変数→コンストラクタ
	cout << endl;
	X loc2 = loc;		// コピーコンストラクタ（X loc2(loc)と同じ）
	cout << endl;
	loc = X(5);			// コンストラクタ + コピー代入 + デストラクタ
	cout << endl;
	loc2 = copy(loc);	// 引数と戻り値のコピーコンストラクタ + コピー代入 + 引数と戻り値のデストラクタ
	cout << endl;
	loc2 = copy2(loc);	// 引数とaのコピーコンストラクタ + コピー代入 + 引数とaのデストラクタ
	cout << endl;
	X loc3(6);			// コンストラクタ
	cout << endl;
	X& r = ref_to(loc);
	cout << endl;
	delete make(7);		// コンストラクタ	+ コピーコンストラクタ + デストラクタ×2
	cout << endl;
	delete make(8);		// 上と同じ
	cout << endl;
	vector<X> v(4);		// デフォルトコンストラクタ×4
	cout << endl;
	XX loc4;			// デフォルトコンストラクタ×2
	cout << endl;
	X* p = new X(9);	// フリーストア上のX→コンストラクタ
	cout << endl;
	delete p;			// デストラクタ
	cout << endl;
	X* pp = new X[5];	// フリーストア上のXの配列→デフォルトコンストラクタ×5
	cout << endl;
	delete[] pp;		// デストラクタ×5
	cout << endl;
}						// loc4のデストラクタ×2、vのデストラクタ×4、loc3、loc2、locのデストラクタ
// グローバル変数globのデストラクタ