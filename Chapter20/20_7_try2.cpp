#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 一致するか
template<class T> bool is_equal(T first, T second, T d_first){
	for(T it = first; it != second; ++it){
		if(*it != *d_first) return false;
		++d_first;
	}
	return true;
}

void test(int* array, int size){
	int right[] = { 1, 2, 3, 4, 5 };

	if(is_equal(array, array + size, right)) cout << "equal" << endl;
	else cout << "not equal" << endl;
}

void test(vector<int>& v){
	vector<int> right = { 1, 2, 3, 4, 5 };

	if(v == right) cout << "equal" << endl;		// is_equal(v.begin(), v.end(), right.begin())
	else cout << "not equal" << endl;
}

void test(list<int>& l){
	list<int> right = { 1, 2, 3, 4, 5 };

	if(l == right) cout << "equal" << endl;		// is_equal(l.begin(), l.end(), right.begin())
	else cout << "not equal" << endl;
}

int main(){
	int array[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(array) / sizeof(array[0]);

	vector<int> vi = { 1, 2, 3, 4, 5 };		// -std=c++11オプション
	list<int> li = { 1, 2, 3, 4, 5 };		// -std=c++11オプション

	test(array, size);
	test(vi);
	test(li);

	// コピー
	int* array2 = new int[size];
	for(int i = 0; i < size; ++i)
		array2[i] = array[i];
	test(array2, size);
	delete[] array2;

	vector<int> vi2 = vi;
	list<int> li2 = li;
	test(vi2);
	test(li2);
}