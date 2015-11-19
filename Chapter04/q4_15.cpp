#include "std_lib_facilities.h"

int main(){
	int n;
	cin >> n;

	int i, j;
	vector<int> primes(1, 2);

	for(i = 3; primes.size() < n; ++i){
		for(j = 0; j < primes.size(); ++j){
			if(i % primes[j] == 0)
				break;
		}

		if(j == primes.size())
			primes.push_back(i);
	}

	for(i = 0; i < primes.size(); ++i)
		cout << primes[i] << endl;
}