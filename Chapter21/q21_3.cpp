#include <iostream>
#include <vector>
using namespace std;

// 関数名をcountからcount2に変更
// 本来は戻り値がiterator_traits<InputIt>::difference_type型 
//           = std::ptrdiff_t型 
//           = implementation-defined（the signed integer type of the result of subtracting two pointers.）
template<class InputIt, class T> 
int count2(InputIt first, InputIt last, const T& value){
	int cnt = 0;
	while(first != last){
		if(*first == value) ++cnt;
		++first;
	}
	return cnt;
}

int main(){
	vector<double> vd(5, 3.14);
	vd[2] = -3.14;
	vd[4] = 0;

	cout << count2(vd.begin(), vd.end(), 3.14) << endl;		// 3
	cout << count2(vd.begin(), vd.end(), -3.14) << endl;	// 1
	cout << count2(vd.begin(), vd.end(), 0.0) << endl;		// 1
	cout << count2(vd.begin(), vd.end(), 2.5) << endl;		// 0
}	