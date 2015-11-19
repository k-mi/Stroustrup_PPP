#include <iostream>
#include <bitset>
using namespace std;

// ビットフィールドの例（25.5.5）
struct PPN{	// R6000の物理ページ番号
	PPN(unsigned int p = 0, unsigned int c = 0, bool nr = false, bool d = false, bool v = false, bool g = false)
		: PFN(p), CCA(c), nonreachable(nr), dirty(d), valid(v), grobal(g) { }

	unsigned int PFN : 22;	// ページフレーム番号（PFN）
	int : 3;				// 未使用
	unsigned int CCA : 3;	// キャッシュコヒーレンシアルゴリズム（CCA）
	bool nonreachable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool grobal : 1;	
};

int main(){
	PPN ppn(0xFFFF, 6, false, false, true, false);

	bitset<32> bs = *reinterpret_cast<unsigned int*>(&ppn);
	cout << bs << endl;

	bs[31] = 1;	// grobal = true
	cout << bs << endl;
}