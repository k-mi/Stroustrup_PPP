#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/*
	テストデータのフォーマット
	シーケンスの定義: { elem1 elem2 elem3 ...}
	シーケンス定義に対するテスト（定義より後）: ( label val res )

	(例)
	{ 1 2 3 5 8 13 21 }
	( 1.1 1 1 )
	( 1.2 5 1 )
	( 1.3 8 1 )
	( 1.4 21 1 )
	( 1.5 -7 0 )
	( 1.6 4 0 )
	( 1.7 22 0 )
*/

// 二分探索
template<class Iter, class T> 
bool bin_search(Iter first, Iter last, const T& value){
	Iter mid = first + (last - first) / 2;

	if(mid != last && *mid == value) return true;
	if(first == mid || mid == last) return false;
	if(*mid < value) return bin_search(mid, last, value);
	if(*mid > value) return bin_search(first, mid, value);
}

template<class T> struct Sequence{
	vector<T> seq;
};

template<class T> struct Test{
	string label;
	T val;
	bool res;
};

template<class T> istream& operator>>(istream& is, Sequence<T>& s){
	if(!is) return is;

	T tmp;
	char ch1, ch2, ch3;
	is >> ch1;
	if(ch1 != '{') return is;

	while(is >> ch2 && ch2 != '}'){
		is.unget();
		is >> tmp;
		s.seq.push_back(tmp);
	}

	if(ch2 != '}') throw runtime_error("input error");
	return is;
}

template<class T> istream& operator>>(istream& is, Test<T>& t){
	if(!is) return is;

	string label;
	T val;
	bool res;
	char ch1, ch2;

	is >> ch1 >> label >> val >> res >> ch2;
	if(!is) return is;
	if(ch1 != '(' || ch2 != ')') throw runtime_error("input error");

	t.label = label;
	t.val = val;
	t.res = res;
	return is;
}

template<class T> int test_all(istream& is){
	int error_count = 0;
	char c;
	Sequence<T> s;	// シーケンス
	Test<T> t;		// テストデータ

	while(is >> c){
		if(c == '{'){
			is.unget();
			s.seq.clear();
			is >> s;
		}
		else if(c == '('){
			is.unget();
			is >> t;

			bool r = bin_search(s.seq.begin(), s.seq.end(), t.val);
			if(r != t.res){
				cout << "failure: test " << t.label
				     << " bin_search: "
				     << s.seq.size() << " elements, val==" << t.val
				     << " -> " << t.res << '\n';
				++error_count; 
			}
		}
		else break;
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