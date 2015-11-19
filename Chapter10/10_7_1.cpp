#include <iostream>
using namespace std;

int main(){
	cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
	int n = 0;
	while(cin >> n){					// 読み取り
		if(1 <= n && n <= 10) break;	// 範囲の確認
		cout << "Sorry " << n << " is not the [1:10] range; please try agein\n";
	}
}