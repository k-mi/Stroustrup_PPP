#include <iostream>
using namespace std;

struct B{
	virtual void f() const { cout << "B::f "; }
	void g() const { cout << "B::g "; }		// 仮想関数ではない
};

struct D : B{
	void f() const { cout << "D::f "; }		// B::fをオーバライドする
	void g() { cout << "D::g "; }
};

struct DD : D{
	void f() { cout << "DD:f "; }			// D::fをオーバーライドしない（constがない）
	void g() const { cout << "DD::g "; }
};

// call関数では、
// DはBの一種なので、Dを受け取ることができる
// DDはDの一種であり、DはBの一種なので、DDを受け取ることができる
void call(const B& b){
	b.f();
	b.g();
}

int main(){
	B b;
	D d;
	DD dd;

	call(b);
	call(d);
	call(dd);

	b.f();
	b.g();

	d.f();
	d.g();

	dd.f();
	dd.g();
}