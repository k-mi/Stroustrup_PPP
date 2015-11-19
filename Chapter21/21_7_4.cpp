#include <iostream>
#include <algorithm>	// copy_if
#include <vector>
using namespace std;

template<class T> class Larger_than{
public:
	Larger_than(const T& vv) : v(vv) { }
	bool operator()(const T& x) { return x > v; }

private:
	T v;
};

int main(){
	vector<int> v(5);
	v[2] = 29;
	v[4] = 32;

	vector<int> v2(v.size());
	copy_if(v.begin(), v.end(), v2.begin(), Larger_than<int>(6));
	
	for(vector<int>::const_iterator it = v2.begin(); it != v2.end(); ++it)
		cout << *it << ' ';
	cout << endl;
}