#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>	// find_if
using namespace std;

struct Item{
	Item() { }
	Item(string n, int i, double v) : name(n), iid(i), value(v) { }

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

// ファイルからアイテムをliに挿入する
void file_input(list<Item>& li, const string& filename){
	ifstream ifs(filename.c_str());
	if(!ifs) return;

	Item tmp;
	while(ifs >> tmp) li.push_back(tmp);
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

class Pred_name{
public:
	Pred_name(const string& s) : name(s) { }
	bool operator()(const Item& i){ return name == i.name; }
private:
	string name;
};

class Pred_iid{
public:
	Pred_iid(int ii) : iid(ii) { }
	bool operator()(const Item& i){ return iid == i.iid; }
private:
	int iid;
};

int main(){
	list<Item> li;
	file_input(li, "drill21_1_input.txt");
	print(li.begin(), li.end());			// 1

	li.sort(Comp_name());
	print(li.begin(), li.end());			// 2 nameでソート

	li.sort(Comp_iid());
	print(li.begin(), li.end());			// 3 iidでソート

	li.sort(Comp_value());
	print(li.begin(), li.end());			// 4 valueで降順にソート

	li.insert(li.begin(), Item("horse shoe", 99, 12.34));
	li.insert(li.begin(), Item("Canon S400", 9988, 499.95));
	print(li.begin(), li.end());			// 5

	li.erase(find_if(li.begin(), li.end(), Pred_name("ASUS RT-AC68U")));
	li.erase(find_if(li.begin(), li.end(), Pred_name("Sony PlayStation 4")));
	print(li.begin(), li.end());			// 6

	li.erase(find_if(li.begin(), li.end(), Pred_iid(9988)));
	li.erase(find_if(li.begin(), li.end(), Pred_iid(8790)));
	print(li.begin(), li.end());			// 7
}