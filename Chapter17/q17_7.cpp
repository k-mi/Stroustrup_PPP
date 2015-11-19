#include <iostream>
using namespace std;

int main(){
	char* p = new char[10];
	char tmp;

	// メモリ枯渇は考慮されない
	for(int i = 0; cin >> tmp && tmp != '!'; ++i)
		p[i] = tmp;	
}