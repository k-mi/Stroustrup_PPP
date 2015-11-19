#include "std_lib_facilities.h"
#include <limits>

int main(){
	int n, tmp, sum = 0;
	vector<int> v;

	cout << "合計したい値の数を入力してください: ";
	cin >> n;
	if(!cin)
		error("処理できない値です。");
	else if(n <= 0)
		error("正の数を入力してください。");

	cout << "整数を入力し、最後に垂直バー(|)を入力してください: ";
	while(cin >> tmp)
		v.push_back(tmp);

	if(n > v.size())
		error("入力された整数が不足しています。");

	cout << "最初の" << n << "個の数字（";
	for(int i = 0; i < n - 1; ++i){
		cout << v[i] << ", ";
		sum += v[i];
	}
	cout << v[n-1] << "）の合計は" << sum + v[n-1] << "です。" << endl;
}