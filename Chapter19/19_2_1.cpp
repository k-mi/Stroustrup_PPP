class vector{
public:
	explicit vector(int s);			// コンストラクタ
	vector(const vector& arg);		// コピーコンストラクタ	
	~vector() { delete[] elem; }	// デストラクタ

	vector& operator=(const vector& a);	// コピー代入

	int size() { return sz; }

	double& operator[](int n) { return elem[n]; }		// 非const vector用（参照を返す）
	double operator[](int n) const { return elem[n]; }	// const vector用（値/const参照を返す）

	void reserve(int newalloc);				// 要素の数を変更する
	int capacity() const { return space; }

	void resize(int newsize);				// 要素の数を変更して、新しい要素をデフォルト値で初期化する

private:
	int sz;			// 要素の数
	double* elem;	// 最初の要素のアドレス
	int space;		// 要素の数 + 新しい要素のための空き領域/スロット
					// （現在の割り当て）

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

// 要素の数を変更する
void vector::reserve(int newalloc){
	if(newalloc <= space) return;		// 割り当てを減らすことはない
	double* p = new double[newalloc];	// 新しい領域を割り当てる
	for(int i = 0; i < sz; ++i)			// 古い領域をコピーする
		p[i] = elem[i];					
	delete[] elem;						// 古い領域の割り当てを解除する
	elem = p;
	space = newalloc;
}

// vectorにnewsize個の要素を持たせる
// 新しい要素をそれぞれデフォルト値0.0で初期化する
void vector::resize(int newsize){
	reserve(newsize);
	for(int i = sz; i < newsize; ++i)	// 新しい要素を初期化する
		elem[i] = 0;
	sz = newsize;
}