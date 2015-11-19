struct X{	// 構造体X
	void f(int x){
		struct Y	// 構造体Y
		{
			int f(){		// Yのメンバ関数
				return 1;
			}
			int m;			// Yのメンバ変数	
		};

		int m;
		m = x;
		Y m2;

		return f(m2.f());	// 再帰 m2.f()は常に1
	}

	int m;				// Xのメンバ変数	

	void g(int m){
		if(m)
			f(m + 2);
		else{
			g(m + 2);	// 0の時のみ再帰 
		}
	}

	X() { }				// Xのコンストラクタ
	void m3() { }		// Xのメンバ関数

	void main(){		// Xのメンバ関数
		X a;
		a.f(2);
	}
};