#include <iostream>
#include <vector>
using namespace std;

void print_vector(ostream& os, const vector<int>& v){
	for(int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	os << endl;
}

int main(){
	// 10
	vector<int> array1(10);
	for(int i = 0, tmp = 1; i < array1.size(); ++i, tmp *= 2)
		array1[i] = tmp;
	vector<int>* p1 = &array1;

	// 11
	vector<int> array2(10);
	vector<int>* p2 = &array2;

	// 12
	for(int i = 0; i < p1->size(); ++i)
		(*p2)[i] = (*p1)[i];

	cout << "p1: " << p1 << ' ';	
	print_vector(cout, *p1);

	cout << "p2: " << p2 << ' ';	
	print_vector(cout, *p2);
}