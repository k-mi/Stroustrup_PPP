#include "std_lib_facilities.h"

void print(string label, const vector<string>& v){
	cout << label << ':' << endl;
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << endl;
}

vector<string> reverse1(const vector<string>& v){
	vector<string> new_vector(v.size());
	for(int i = 0; i < v.size(); ++i)
		new_vector[i] = v[v.size() - 1 - i];

	return new_vector;
}

void reverse2(vector<string>& v){
	for(int i = 0; i < v.size() / 2; ++i)
		swap(v[i], v[v.size() - 1 - i]);
}

int main(){
	vector<string> v(5, "apple");
	v[2] = "banana";
	v[3] = "chocolate";

	reverse1(v);
	print("reverse1", v);
	print("reverse1", reverse1(v));

	reverse2(v);
	print("reverse2", v);
}