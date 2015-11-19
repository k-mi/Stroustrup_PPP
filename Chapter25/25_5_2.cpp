#include <iostream>
#include <bitset>	// bitset
using namespace std;

int main(){
	const int max = 10;
	bitset<max> b;
	while(cin >> b){
		cout << b << '\n';
		for(int i = 0; i < max; ++i) cout << b[i];	// 逆の順序
		cout << '\n';
	}
}