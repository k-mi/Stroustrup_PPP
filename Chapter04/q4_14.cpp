#include "std_lib_facilities.h"

int main(){
	int max;
	cin >> max;
	vector<short> primes(max + 1, 1);

	for(int i = 2; i <= max; ++i)
		if(primes[i] == 1)
			for(int j = i * 2; j <= max; j += i)
				primes[j] = 0;
	
	for(int i = 2; i <= max; ++i)
		if(primes[i] == 1)
			cout << i << endl;
}