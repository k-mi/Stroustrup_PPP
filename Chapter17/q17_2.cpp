#include <iostream>
using namespace std;

// 型のサイズを求める
template<typename T> int size(){
	T t[2];
	return reinterpret_cast<long long>(&t[1]) - reinterpret_cast<long long>(&t[0]);
}

int main(){
	cout << "int: " << size<int>() << endl;
	cout << "double: " << size<double>() << endl;
	cout << "bool: " << size<bool>() << endl;

	cout << endl;

	cout << "int: " << sizeof(int) << endl;
	cout << "double: " << sizeof(double) << endl;
	cout << "bool: " << sizeof(bool) << endl;
}