#include <iostream>
using namespace std;

class B1{
public:
	virtual void vf() { cout << "B1::vf()" << endl; }
	void f() { cout << "B1::f()" << endl; }
};

class D1 : public B1{
public:
	void vf() { cout << "D1::vf()" << endl; }
	void f() { cout << "D1::f()" << endl; }
};

int main(){
	B1 b1;
	D1 d1;
	B1& b1r = d1;

	b1.vf();	// B1
	b1.f();		// B1

	d1.vf();	// D1
	d1.f();		// D1 この場合のみ結果がdrill14_1～3と異なる。独自の関数が存在するためD1が呼び出される。

	b1r.vf();	// D1
	b1r.f();	// B1 仮想関数でない場合はvtblが作成されないため、実際のオブジェクトの型ではなく参照の型の関数が呼び出される。
}