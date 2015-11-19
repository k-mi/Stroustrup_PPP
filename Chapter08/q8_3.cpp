#include "std_lib_facilities.h"

void print(string label, const vector<int>& v){
	cout << label << ':' << endl;
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << endl;
}

void fibonacci(int x, int y, vector<int>& v, int n){
	v.push_back(x);
	v.push_back(y);

	for(int i = 2; i < n; ++i)
		v.push_back(v[i-2] + v[i-1]);
}

int main(){
	vector<int> v;
	fibonacci(1, 2, v, 10);
	print("fibonacci(1, 2, v, 10)", v);

	vector<int> w;
	fibonacci(1, 1, w, 20);
	print("fibonacci(1, 1, w, 20)", w);
}