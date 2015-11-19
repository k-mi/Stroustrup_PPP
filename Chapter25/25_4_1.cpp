template<class T> class Array_ref{
public:
	Array_ref(T* pp, int s) : p(pp), sz(s) { }

	T& operator[](int n) { return p[n]; }
	const T& operator[](int n) const { return p[n]; }

	bool assign(Array_ref a){
		if(a.sz != sz) return false;
		for(int i = 0; i < sz; ++i)
			p[i] = a.p[i];
		return true;
	}

	void reset(Array_ref a) { reset(a.p, a.sz); }
	void reset(T* pp, int s) { p = pp; sz = s; }

	int size() const { return sz; }

	// デフォルトのコピー操作: 
	// Array_refはリソースをいっさい所有しない
	// Array_refには参照のセマンティクスがある
private:
	T* p;
	int sz;
};

template<class T> Array_ref<T> make_ref(T* pp, int s){
	return (pp) ? Array_ref<T>(pp, s) : Array_ref<T>(nullptr, 0);
}

template<class T> Array_ref<T> make_ref(vector<T>& v){
	return (v.size()) ? Array_ref<T>(&v[0], v.size()) : Array_ref<T>(nullptr, 0);
}

template<class T, int s> Array_ref<T> make_ref(T (&pp)[s]){
	return Array_ref<T>(pp, s);
}