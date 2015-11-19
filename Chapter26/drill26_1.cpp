// 簡単なテストハーネス(26.3.2.2)の3つ目の例

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

// 二分探索
template<class Iter, class T> 
bool bin_search(Iter first, Iter last, const T& value){
	Iter mid = first + (last - first) / 2;

	if(mid != last && *mid == value) return true;
	if(first == mid || mid == last) return false;
	if(*mid < value) return bin_search(mid, last, value);
	if(*mid > value) return bin_search(first, mid, value);
}

struct Test{
	string label;
	int val;
	vector<int> seq;
	bool res;
};

istream& operator>>(istream& is, Test& t){
	if(!is) return is;

	string label;
	int val, tmp;
	vector<int> seq;
	bool res;
	char ch1, ch2, ch3, ch4;

	is >> ch1;
	if(ch1 != '{') throw is;

	is >> label >> val >> ch2;
	if(ch2 != '{') throw runtime_error("input error");

	while(is >> ch3 && ch3 != '}'){
		is.unget();
		is >> tmp;
		seq.push_back(tmp);
	}

	is >> res >> ch4;
	if(ch4 != '}') throw runtime_error("input error");

	t.label = label;
	t.val = val;
	t.seq = seq;
	t.res = res;
	return is;
}

int test_all(istream& is){
	int error_count = 0;
	Test t;
	while(is >> t){
		bool r = bin_search(t.seq.begin(), t.seq.end(), t.val);
		if(r != t.res){
			cout << "failure: test " << t.label
			     << " bin_search: "
			     << t.seq.size() << " elements, val==" << t.val
			     << " -> " << t.res << '\n';
			++error_count; 
		}
	}
	return error_count;
}

int main(){
	string filename;
	cout << "input testfile: ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs){
		cerr << "no " << filename << endl;
		return 0;
	}

	int errors = test_all(ifs);
	cout << "number of errors: " << errors << "\n";
}