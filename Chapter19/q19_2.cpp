#include <iostream>
#include <vector>
using namespace std;

// すべてのvt[i]*vu[i]の合計を返す
template<class T, class U> double vector_multi(const vector<T>& vt, const vector<U>& vu){
	double add = 0;
	for(int i = 0; i < vt.size() && i < vu.size(); ++i)
		add += vt[i] * vu[i];
	return add;
}

int main(){
	vector<int> v1(20, 100);
	vector<double> v2(30, 3.14);

	cout << vector_multi(v1, v2) << endl;
}