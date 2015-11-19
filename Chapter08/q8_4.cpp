#include "std_lib_facilities.h"

void fibonacci(int x, int y, vector<int>& v, int n){
	v.push_back(x);
	v.push_back(y);

	for(int i = 2; i < n; ++i)
		v.push_back(v[i-2] + v[i-1]);
}

int main(){
	vector<int> v;
	fibonacci(1, 1, v, 50);
	
	for(int i = 0; i < v.size(); ++i){
		if(v[i] < 0){
			cout << v[i-1] << endl;
			break;
		}
	}
}