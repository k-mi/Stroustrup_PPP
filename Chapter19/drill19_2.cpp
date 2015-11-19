template<class T> struct S {
	explicit S(T v) : val(v) { }	// コンストラクタ

	T val; 							// 値
};