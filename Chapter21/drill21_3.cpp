#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>	// copy, copy_if, sort
#include <numeric>		// accumulate
#include <iterator>		// reverse
using namespace std;

void file_input(vector<double>& vd, const string& filename){
	ifstream ifs(filename);
	if(!ifs) return;

	double tmp;
	while(ifs >> tmp) vd.push_back(tmp);
}

template<class Iter> void print(Iter first, Iter last){
	while(first != last)
		cout << *(first++) << ' ';
	cout << endl;
}

template<class T> class Less_than{
public:
	Less_than(T n) : num(n) { }
	bool operator()(const T& x) { return x < num; }
private:
	T num;
};

int main(){
	// 1
	vector<double> vd;
	file_input(vd, "drill21_3_input.txt");

	// 2
	print(vd.begin(), vd.end());

	// 3
	vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());
	print(vi.begin(), vi.end());

	// 4
	for(int i = 0; i < vd.size(); ++i)
		cout << '(' << vd[i] << ',' << vi[i] << ')' << endl;

	// 5
	double ad = accumulate(vd.begin(), vd.end(), 0.0);
	cout << ad << endl;

	// 6
	int ai = accumulate(vi.begin(), vi.end(), 0);
	cout << ad - ai << endl;

	// 7
	reverse(vd.begin(), vd.end());
	print(vd.begin(), vd.end());

	// 8
	double ave = ad / vd.size();
	cout << "Ave: " << ave << endl;

	// 9
	vector<double> vd2(vd.size());
	copy_if(vd.begin(), vd.end(), vd2.begin(), Less_than<double>(ave));
	print(vd2.begin(), vd2.end());

	// 10
	sort(vd.begin(), vd.end());
	print(vd.begin(), vd.end());
}