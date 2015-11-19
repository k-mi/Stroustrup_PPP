// 非常に単純なdouble型のvector
class vector{
public:
	vector(int s)				// コンストラクタ 
		: sz(s), 				// szを初期化する
		elem(new double[s])		// elemを初期化する
	{
		for(int i = 0; i < s; ++i)
			elem[i] = 0;		// 要素を初期化する
	}

	int size() { return sz; }	// 現在のサイズ

	void clean_up() { delete[] elem; }

private:
	int sz;						// サイズ
	double* elem;				// 要素へのポインタ
};

// メモリリーク
void f1(int n){
	vector v(n);
	// ...
}

void f2(int n){
	vector v(n);
	// vを使用する
	v.clean_up();
}

int main(){
	f2(10000);
}