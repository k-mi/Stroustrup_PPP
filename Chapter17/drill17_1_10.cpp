#include <iostream>
#include <vector>
using namespace std;

void print_vector(ostream& os, const vector<int>& v){
	for(int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	os << endl;
}

int main(){
	// 5
	vector<int> array1(10);
	for(int i = 0; i < array1.size(); ++i)
		array1[i] = i + 100;

	print_vector(cout, array1);
	cout << endl;

	// 6
	vector<int> array2(11);
	for(int i = 0; i < array2.size(); ++i)
		array2[i] = i + 100;

	print_vector(cout, array2);
	cout << endl;

	// 8
	vector<int> array3(20);
	for(int i = 0; i < array3.size(); ++i)
		array3[i] = i + 100;

	print_vector(cout, array3);
}