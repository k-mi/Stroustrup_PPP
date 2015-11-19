#include <vector>
#include "Graph.h"
using namespace std;
using namespace Graph_lib;

template<class T> class Array_ref {
public:
	Array_ref(T* pp, int s) : p(pp), sz(s) { }

	T& operator[](int n) { return p[n]; }
	const T& operator[](int n) const { return p[n]; }

	bool assign(Array_ref a) {
		if(a.sz != sz) return false;
		for(int i = 0; i < sz; ++i)
			p[i] = a.p[i];
		return true;
	}

	void reset(Array_ref a) { reset(a.p, a.sz); }
	void reset(T* pp, int s) { p = pp; sz = s; }

	int size() const { return sz; }

	// �f�t�H���g�̃R�s�[����: 
	// Array_ref�̓��\�[�X�������������L���Ȃ�
	// Array_ref�ɂ͎Q�Ƃ̃Z�}���e�B�N�X������
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

void f(Shape* q, vector<Circle>& s0) {
	Graph_lib::Polygon s1[10];
	//Shape s2[10];				// Shape�Ƀf�t�H���g�R���X�g���N�^�͑��݂��Ȃ�

	// ������
	Shape* p1 = new Graph_lib::Rectangle(Point(0, 0), Point(10, 20));

	//better(make_ref(s0));		// #1 �G���[: Array_ref<Shape>���K�v
	//better(make_ref(s1));		// #2 �G���[: Array_ref<Shape>���K�v
	//better(make_ref(s2));		// #3 OK:�is2��OK�ł���ꍇ�j
	better(make_ref(p1, 1));	// #4 OK: 1�̗v�f
	delete p1;
	p1 = 0;
	better(make_ref(p1, 1));	// #5 OK: �v�f�Ȃ�
	//better(make_ref(q, max));	// #6 OK:�imax��OK�ł���ꍇ�j
}

int main() {
	vector<Circle> vc;
	Circle* c = new Circle(Point(100, 100), 20);

	f(c, vc);

	delete c;
}