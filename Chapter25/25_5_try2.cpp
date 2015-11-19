#include <iostream>
using namespace std;

template<class T> void print(T i) { cout << i << '\t'; }
void print(char i) { cout << int(i) << '\t'; }
void print(signed char i) { cout << int(i) << '\t'; }
void print(unsigned char i) { cout << int(i) << '\t'; }

int main(){
	int si;
	while(cin >> si){
		char c = si;	// charへの暗黙的な変換
		unsigned char uc = si;
		signed char sc = si;
		print(si); print(c); print(uc); print(sc); cout << '\n';		
	}
}