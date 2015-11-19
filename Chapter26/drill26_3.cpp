#include <iostream>
#include <vector>
#include <cstdlib>	// rand
#include <string>	// to_string (C++11)
#include <ctime>	// time
using namespace std;

int randint(int n){
	if(n == 0) return 0;
	else return rand() % n;
}

// ラベルlabのテストの詳細をcoutに書き出す
// baseから始まるn個の要素のシーケンスを生成する
// 要素間の平均的な距離は[0: spread）の等分布
void make_test(const string& lab, int n, int base, int spread){
	vector<int> v;
	int elem = base;
	for(int i = 0; i < n; ++i){
		elem += randint(spread);
		v.push_back(elem);
	}

	int val = base + randint(elem - base);		// 検索する値を作成する
	cout << "{" << lab << " " << val << " {";	// 注意: コードの移動して変数をnからvalに変更

	bool found = false;
	for(int i = 0; i < n; ++i){	// 要素を出力し、valが含まれているかどうかを確認する
		if(v[i] == val) found = true;
		cout << v[i] << " ";
	}
	cout << "} " << found << " }\n";
}

int main(){
	srand(time(0));

	// a.非常に大きなシーケンス
	make_test("large_test", 1000000, 0, randint(50));

	// b.ランダムな数の要素を持つ10個のシーケンス
	for(int i = 0; i < 10; ++i){
		string lab = "rand_test_";
		make_test(lab + to_string(i), randint(500), 0, randint(50));
	}	

	// c.0、1、2...9個のランダムな要素を持つ10個のシーケンス
	for(int i = 0; i < 10; ++i){
		string lab = "rand(0-9)_test_";
		make_test(lab + to_string(i), i, 0, randint(50));
	}	
}