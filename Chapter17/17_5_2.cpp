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

	~vector() {					// デストラクタ
		delete[] elem; 			// メモリを解放する
	}	

private:
	int sz;						// サイズ
	double* elem;				// 要素へのポインタ
};

void f3(int n){
	double* p = new double[n];	// n個のdoubleを割り当てる
	vector v(n);				// vectorを割り当てる（n個のdoubleを別に割り当てる）
	// pとvを使用する
	delete[] p;					// doubleの割り当てを解除する
}	// vectorはvを自動的にクリーンアップする

int main(){
	f3(10000);
}