#include <iostream>
using namespace std;

namespace X{
	int var;
	void print(){
		cout << var << endl;
	}
}

namespace Y{
	int var;
	void print(){
		cout << var << endl;
	}
}

namespace Z{
	int var;
	void print(){
		cout << var << endl;
	}
}

int main(){
	X::var = 7;
	X::print();	// Xのvarを出力する
	using namespace Y;
	var = 9;
	print();	// Yのvarを出力する
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();	// Zのvarを出力する
	}
	print();	// Yのvarを出力する
	X::print();	// Xのvarを出力する
}