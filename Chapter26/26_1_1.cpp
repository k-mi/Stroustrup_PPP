#include <iostream>
#include <vector>
#include <utility>	// make_pair
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
	vector<int> vi(10);
	for(int i = 0; i < vi.size(); ++i)
		vi[i] = i * 2;

	for(int i = 0; i <= vi.size() * 2; ++i)
		cout << i << ": " << (bin_search(vi.begin(), vi.end(), i).second ? "true" : "false") << endl;
}