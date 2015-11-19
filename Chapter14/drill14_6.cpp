#include <iostream>
using namespace std;

class B1{
public:
	virtual void vf() { cout << "B1::vf()" << endl; }
	void f() { cout << "B1::f()" << endl; }
	virtual void pvf() = 0;		// 純粋仮想関数（pure virtual function）
};

class D1 : public B1{
public:
	void vf() { cout << "D1::vf()" << endl; }		// オーバーライド
	void f() { cout << "D1::f()" << endl; }
	void pvf() { cout << "D1::pvf()" << endl; }		// オーバーライド
};

class D2 : public D1{
public:
	void pvf() { cout << "D2::pvf()" << endl; }		// さらにオーバーライド
};

int main(){
	// B1 b1;	// 抽象クラスであるためオブジェクトを作成することはできない。
	D1 d1;
	D2 d2;


	d1.vf();	// D1
	d1.f();		// D1
	d1.pvf();	// D1

	d2.vf();	// D1
	d2.f();		// D1
	d2.pvf();	// D2	// 呼び出し元のオブジェクトの型に対応する関数が呼び出される。
}