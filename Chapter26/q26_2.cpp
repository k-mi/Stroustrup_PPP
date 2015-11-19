// q26_1.cppのテンプレート化

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
	string filename1, filename2;
	cout << "input testfile (double): ";
	cin >> filename1;
	ifstream ifs1(filename1.c_str());
	cout << "input testfile (string): ";
	cin >> filename2;
	ifstream ifs2(filename2.c_str());
	if(!ifs1 || !ifs2){
		cerr << "error input file" << endl;
		return 0;
	}

	int errors = test_all<double>(ifs1);
	cout << "number of errors (double): " << errors << "\n";

	errors = test_all<string>(ifs2);
	cout << "number of errors (string): " << errors << "\n";
}