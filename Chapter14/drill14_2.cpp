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
};

int main(){
	B1 b1;
	D1 d1;

	b1.vf();
	b1.f();

	d1.vf();
	d1.f();
}