#include <iostream>
#include <vector>
#include <utility>		// make_pair
#include <algorithm>	// sort
using namespace std;

// 二分探索
template<class Iter, class T> 
pair<Iter, bool> bin_search(Iter first, Iter last, const T& value){
	Iter mid = first + (last - first) / 2;

	if(mid != last && *mid == value) return make_pair(mid, true);
	if(first == mid || mid == last) return make_pair(mid, false);
	if(*mid < value) return bin_search(mid, last, value);
	if(*mid > value) return bin_search(first, mid, value);
}

int main(){
	int n;
	vector<int> vi;

	cout << "input vector<int>: " << endl;
	while(cin >> n && n >= 0)
		vi.push_back(n);

	sort(vi.begin(), vi.end());

	cout << "search: " << endl;
	while(cin >> n && n >= 0)
		cout << (bin_search(vi.begin(), vi.end(), n).second ? "true" : "false") << endl;
}