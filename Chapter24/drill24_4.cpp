#include <iostream>
#include <cerrno>	// errno
#include <cmath>
using namespace std;

int main(){
	int n;
	cin >> n;

	errno = 0;
	double d = sqrt(n);
	if(errno)	// Darwin上では動作しないかも
		cout << "no square root" << endl;
	else
		cout << d << endl;
}