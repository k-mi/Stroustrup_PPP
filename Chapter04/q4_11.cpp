#include "std_lib_facilities.h"

int main(){
	int i, j;
	vector<int> primes(1, 2);

	for(i = 3; i <= 100; ++i){
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