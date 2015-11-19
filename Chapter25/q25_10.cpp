#include <iostream>
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

void print_ppn(PPN* p){
	cout << "PFN: " << hex << p->PFN << endl
		 << "CCA: " << hex << p->CCA << endl
		 << "nonreachable: " << (p->nonreachable ? "true" : "false") << endl
		 << "dirty: " << (p->dirty ? "true" : "false") << endl
		 << "valid: " << (p->valid ? "true" : "false") << endl
		 << "grobal: " << (p->grobal ? "true" : "false") << endl << endl;
}

int main(){
	PPN ppn;
	print_ppn(&ppn);
	ppn.PFN = 0x00FFFF;
	ppn.valid = true;
	print_ppn(&ppn);

	unsigned int ui = 0;
	print_ppn(reinterpret_cast<PPN*>(&ui));
	ui |= 0xFFFF;	// PFN = 0xFFFF
	ui |= 1 << 31;	// grobal = true
	print_ppn(reinterpret_cast<PPN*>(&ui));
}