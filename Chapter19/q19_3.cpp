#include <iostream>
#include <algorithm>
using namespace std;

// 任意の型のペアを格納できるテンプレートクラス
template<class T1, class T2> struct Pair{
	Pair(T1 f = T1(), T2 s = T2()) : first(f), second(s) { }
	Pair(T1& f, T2& s) : first(f), second(s) { }

	T1 first;
	T2 second;
};

int main(){
	Pair<int, string> p1(12, "Apple"), p2;
	cout << "p1: " << p1.first << ' ' << p1.second << endl;
	cout << "p2: " << p2.first << ' ' << p2.second << endl;
}