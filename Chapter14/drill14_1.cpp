#include <iostream>
using namespace std;

class B1{
public:
	virtual void vf() { cout << "B1::vf()" << endl; }
	void f() { cout << "B1::f()" << endl; }
};

int main(){
	B1 b1;

	b1.vf();
	b1.f();
}