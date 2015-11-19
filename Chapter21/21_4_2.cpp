#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>	// strncmp
using namespace std;

struct Record{
	string name;	// 使いやすさを考慮して、標準のstringを使用する
	char addr[24];	// データベースレイアウトと一致する古いスタイル
	// ...
};

// Recordオブジェクトの比較
struct Cmp_by_name{
	bool operator()(const Record& a, const Record& b) const{
		return a.name < b.name;
	}
};

struct Cmp_by_addr
{
	bool operator()(const Record& a, const Record& b) const{
		return strncmp(a.addr, b.addr, 24) < 0;
	}
};

int main(){
	vector<Record> vr;

	sort(vr.begin(), vr.end(), Cmp_by_name());	// nameでソートする
	sort(vr.begin(), vr.end(), Cmp_by_addr());	// addrでソートする	
}
