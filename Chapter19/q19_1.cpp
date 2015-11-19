#include <iostream>
#include <vector>
using namespace std;

// v2の要素をv1に追加する
template<class T> void f(vector<T>& v1, const vector<T>& v2){
	for(int i = 0; i < v1.size() && i < v2.size(); ++i)
		v1[i] += v2[i];
}

int main(){
	vector<int> v1(60, 20);
	vector<int> v2(30, 80);

	f(v1, v2);
	cout << v1[29] << endl;
	cout << v1[59] << endl;
}