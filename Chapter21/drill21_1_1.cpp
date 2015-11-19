#include <iostream>
#include <fstream>
#include <vector>
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

int main(){
	vector<Item> vi;
	file_input(vi, "drill21_1_input.txt");
	print(vi.begin(), vi.end());
}