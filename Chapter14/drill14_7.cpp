#include <iostream>
#include <string>
using namespace std;

class B2{
public:
	virtual void pvf() = 0;		// 純粋仮想関数（pure virtual function）
};

class D21 : public B2{
public:
	void pvf() { cout << s << endl; }
private:
	string s = "21";
};

class D22 : public B2{
public:
	void pvf() { cout << i << endl; }
private:
	int i = 22;
};

void f(B2& b2){
	b2.pvf();
}

int main(){
	D21 d21;
	D22 d22;

	//参照先のオブジェクトの型で定義されたpvf()が呼び出される。
	f(d21);	// "21"
	f(d22);	// "22"
}