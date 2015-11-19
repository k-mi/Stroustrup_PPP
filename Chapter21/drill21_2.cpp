#include <iostream>
#include <map>
#include <utility>	// pair
#include <numeric>	// accumulate
using namespace std;

// 3: pairをcoutへ出力
template<class Iter> void print_pair(Iter first, Iter last){
	while(first != last){
		cout << first->first << ", " << first->second << endl;
		++first;
	}
	cout << endl;
}

// 5: cinから値のペアを読み取りmsiに配置する
void input_pair(map<string, int>& msi){
	string key;
	int value;
	cin >> key >> value;
	if(cin) msi.insert(pair<string, int>(key, value));
}

// 8: アキュムレータにkeyを加算する関数オブジェクト
template<class A, class S> struct Plus_key{
	A operator()(const A& accumulator, const S& sequence){
		return accumulator + sequence.second;
	}
};

int main(){
	// 1
	map<string, int> msi;

	// 2
	msi["lecture"] = 21;
	msi["apple"] = 2;
	msi["banana"] = 7;
	msi["hall"] = 4;
	msi["coach"] = 10;
	msi["gave"] = 23;
	msi["punctual"] = 22;
	msi["attend"] = 13;
	msi["practice"] = 17;
	msi["conversation"] = 25;

	// 3
	print_pair(msi.begin(), msi.end());

	// 4
	msi.erase("hall");
	print_pair(msi.begin(), msi.end());

	// 6
	for(int i = 0; i < 10; ++i) input_pair(msi);

	// 7
	print_pair(msi.begin(), msi.end());

	// 8
	cout << "sum: " << accumulate(msi.begin(), msi.end(), 0, 
						Plus_key<int, pair<string, int> >()) << "\n\n";

	// 9
	map<int, string> mis;

	// 10
	for(map<string, int>::const_iterator it = msi.begin(); it != msi.end(); ++it)
		mis[it->second] = it->first;

	// 11
	print_pair(mis.begin(), mis.end());
}