#include <vector>
#include "Graph.h"
using namespace std;
using namespace Graph_lib;

template<class T> class Array_ref {
public:
	Array_ref(T* pp, int s) : p(pp), sz(s) { }

	T& operator[](int n) { return p[n]; }
	const T& operator[](int n) const { return p[n]; }

	template<class Q> operator const Array_ref<const Q>() {
		// 要素の暗黙的な変換をチェックする
		static_cast<Q>(static_cast<T*>(nullptr));

		// Array_refの型変換
		return Array_ref<const Q>(reinterpret_cast<Q*>(p), sz);
	}

	bool assign(Array_ref a) {
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

template<class T> Array_ref<T> make_ref(T* pp, int s) {
	return (pp) ? Array_ref<T>(pp, s) : Array_ref<T>(nullptr, 0);
}

template<class T> Array_ref<T> make_ref(vector<T>& v) {
	return (v.size()) ? Array_ref<T>(&v[0], v.size()) : Array_ref<T>(nullptr, 0);
}

template<class T, int s> Array_ref<T> make_ref(T(&pp)[s]) {
	return Array_ref<T>(pp, s);
}

void better(Array_ref<Shape> a) {
	for(int i = 0; i < a.size(); ++i) a[i].draw();
}

void better2(const Array_ref<Shape* const> a) {
	for(int i = 0; i < a.size(); ++i)
		if(a[i]) 
			a[i]->draw();
}

void f(Shape* q, vector<Circle>& s0) {
	Graph_lib::Polygon s1[10];
	//Shape s2[10];				// Shapeにデフォルトコンストラクタは存在しない

	// 初期化
	Shape* p1 = new Graph_lib::Rectangle(Point(0, 0), Point(10, 20));

	better2(make_ref(s0));		// #1 OK: Array_ref<Shape* const>に変換する
	//better2(make_ref(s1));	// #2 OK:（s1がOKである場合）
	//better2(make_ref(s2));	// #3 OK:（s2がOKである場合）
	better(make_ref(p1, 1));	// #4 OK: 1つの要素
	delete p1;
	p1 = 0;
	better(make_ref(p1, 1));	// #5 OK: 要素なし
	//better(make_ref(q, max));	// #6 OK:（maxがOKである場合）
}

int main() {
	vector<Circle> vc;
	Circle* c = new Circle(Point(100, 100), 20);

	f(c, vc);

	delete c;
}