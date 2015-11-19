#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

// 比較条件を受け取る二分探索
template<class Iter, class T, class Compare> 
bool bin_search(Iter first, Iter last, const T& value, Compare comp){
	Iter mid = first + (last - first) / 2;

	if(mid != last && *mid == value) return true;
	if(first == mid || mid == last) return false;
	if(comp(*mid, value)) return bin_search(mid, last, value, comp);
	else return bin_search(first, mid, value, comp);
}

// 比較のテストのための関数テンプレート
template<class T1, class T2> struct Comp_t{
	bool operator()(const T1& elem, const T2& val) const{
		return elem < val;	// 引数をそのまま比較
	}
};

template<class T> struct Test{
	string label;
	T val;
	vector<T> seq;
	bool res;
};

template<class T> istream& operator>>(istream& is, Test<T>& t){
	if(!is) return is;

	string label;
	T val, tmp;
	vector<T> seq;
	bool res;
	char ch1, ch2, ch3, ch4;

	is >> ch1;
	if(ch1 != '{') return is;

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

template<class T> int test_all(istream& is){
	int error_count = 0;
	Test<T> t;
	while(is >> t){
		// 注意: テストセットの入力がq26_1.cppと同じままなので、型の異なる比較条件は指定不可
		bool r = bin_search(t.seq.begin(), t.seq.end(), t.val, Comp_t<T, T>());
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

	int errors = test_all<int>(ifs);	
	cout << "number of errors: " << errors << "\n";
}