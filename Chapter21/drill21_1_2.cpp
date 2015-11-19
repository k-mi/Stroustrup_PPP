#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>	// sort
using namespace std;

struct Item{
	string name;
	int iid;
	double value;
};

// 各行1アイテムのcsv形式を入力
istream& operator>>(istream& is, Item& i){
	string name = "";

	while(true){
		char c = is.get();
		if(!is) return is;

		if(c == '\n') continue;	// 改行は無視
		else if(c != ',') name += c;
		else break;
	}

	char ch;
	int iid;
	double value;
	is >> iid >> ch >> value;
	if(!is || ch != ',') return is;

	i.name = name;
	i.iid = iid;
	i.value = value;

	return is;
}

ostream& operator<<(ostream& os, const Item& i){
	if(!os) return os;
	os << i.name << ", " << i.iid << ", " << i.value;
	return os;
}

// ファイルからアイテムをviに挿入する
void file_input(vector<Item>& vi, const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) return;

	Item tmp;
	while(ifs >> tmp) vi.push_back(tmp);
}

// coutへアイテムを出力
template<class Iter> void print(Iter first, Iter last){
	while(first != last) cout << *(first++) << endl;
	cout << endl;
}

// アイテムのnameで比較
struct Comp_name{
	bool operator()(const Item& i1, const Item& i2){
		return i1.name < i2.name;
	}
};

// アイテムのiidで比較
struct Comp_iid{
	bool operator()(const Item& i1, const Item& i2){
		return i1.iid < i2.iid;
	}
};

// アイテムのvalueで比較（降順）
struct Comp_value{
	bool operator()(const Item& i1, const Item& i2){
		return i1.value > i2.value;
	}
};

int main(){
	vector<Item> vi;
	file_input(vi, "drill21_1_input.txt");
	print(vi.begin(), vi.end());			// 1

	sort(vi.begin(), vi.end(), Comp_name());
	print(vi.begin(), vi.end());			// 2 nameでソート

	sort(vi.begin(), vi.end(), Comp_iid());
	print(vi.begin(), vi.end());			// 3 iidでソート

	sort(vi.begin(), vi.end(), Comp_value());
	print(vi.begin(), vi.end());			// 4 valueで降順にソート
}