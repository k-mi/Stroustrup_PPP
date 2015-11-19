#include <iostream>
#include <iterator>	// distance, advance
#include <vector>
#include <list>
using namespace std;

// [first:end)にvalueと等価な要素が存在するか？
template<class Iter, class T> 
bool bin_search(Iter first, Iter last, const T& value){
//	Iter mid = first + (last - first) / 2;
	Iter mid = first;
	advance(mid, distance(first, last) / 2);

	if(mid != last && *mid == value) return true;
	else if(mid != first && mid != last && *mid > value) return bin_search(first, mid, value);
	else if(mid != first && mid != last && *mid < value) return bin_search(mid, last, value);
	else return false;
}

int main(){	// 各出力は0: false, 1: true
	vector<int> vi(10);
	for(int i = 0; i < vi.size(); ++i) 
		vi[i] = i * 2;

	for(int i = 0; i <= 20; ++i)
		cout << i << ": " << bin_search(vi.begin(), vi.end(), i) << endl;

	list<string> vl;
	vl.push_back("Banana");
	vl.push_back("Apple");
	vl.push_back("Mashroom");
	vl.push_back("Chocorate");
	vl.push_back("Radish");
	vl.sort();

	cout << "Apple: " << bin_search(vl.begin(), vl.end(), "Apple") << endl;
	cout << "Radish: " << bin_search(vl.begin(), vl.end(), "Radish") << endl;
	cout << "Mikan: " << bin_search(vl.begin(), vl.end(), "Mikan") << endl;
}