#include <iostream>
#include <cstdlib>	// rand
#include <map>
using namespace std;

int randint(int n){
	return rand() % n;
}

int main(){
	int n, d;

	while(cin >> n >> d && n > 0 && d > 0){
		map<int, int> count;

		for(int i = 0; i < d; ++i) 
			++count[randint(n)];

		for(int i = 0; i < n; ++i)
			cout << i << ": " << count[i] << endl;
	}
}