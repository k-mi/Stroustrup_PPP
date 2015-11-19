#include <iostream>
using namespace std;

class Member{
public:
	Member() : a("Apple"){
		cout << "Member::Member()" << endl;
	}

	~Member(){
		cout << "Member::~Member()" << endl;
	}

private:
	string a;
};

class Base{
public:
	Base(){
		cout << "Base::Base()" << endl;
	}

	// virtualにしないと、基底のポインタを通じて削除された
	// 派生クラスのオブジェクトのデストラクタが呼ばれないため
	// メモリリークが発生する可能性がある
	virtual ~Base(){	
		cout << "Base::~Base()" << endl;
	}
};

class Derivation : public Base{
public:
	Derivation(){
		cout << "Derivation::Derivation()" << endl;
	}

	~Derivation(){
		cout << "Derivation::~Derivation()" << endl;
	}

private:
	Member m;
};

int main(){
	Base* p = new Derivation();
	cout << endl;
	delete p;		// 基底のポインタを通じて削除

	cout << endl;

	p = new Base();
	cout << endl;
	delete p;
}