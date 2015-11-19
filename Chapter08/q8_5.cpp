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

vector<int> reverse1(const vector<int>& v){
	vector<int> new_vector(v.size());
	for(int i = 0; i < v.size(); ++i)
		new_vector[i] = v[v.size() - 1 - i];

	return new_vector;
}

void reverse2(vector<int>& v){
	for(int i = 0; i < v.size() / 2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
}

int main(){
	vector<int> v;
	fibonacci(1, 1, v, 10);

	reverse1(v);
	print("reverse1", v);
	print("reverse1", reverse1(v));

	reverse2(v);
	print("reverse2", v);
}