// 非常に単純な（vector<double>と同様の）double型のvector
class vector{
public:
	vector(int s);	// コンストラクタ:
					// doubleを割り当て、elemにそれらをポイントさせ
					// szにsを格納する
	int size() const { return sz; } // 現在のサイズ

private:
	int sz;			// サイズ
	double* elem;	// 最初の（double型の）要素へのポインタ
};