#include <iostream>
#include <vector>
using namespace std;

// 関数名をcount_ifからcount_if2に変更
// 本来は戻り値がiterator_traits<InputIt>::difference_type型 
//           = std::ptrdiff_t型 
//           = implementation-defined（the signed integer type of the result of subtracting two pointers.）
template<class InputIt, class UnaryPredicate>
int count_if2(InputIt first, InputIt last, UnaryPredicate p){
	int cnt = 0;
	while(first != last){
		if(p(*first)) ++cnt;
		++first;
	}
	return cnt;
}

// x未満かどうか判定する関数オブジェクト
template<class T> class Less_pred{
public:
	Less_pred(T xx) : x(xx) { }
	bool operator()(const T& y) { return y < x; }
private:
	T x;
};

int main(){
	vector<double> vd(5, 3.14);
	vd[2] = -3.14;
	vd[4] = 0;

	cout << count_if2(vd.begin(), vd.end(), Less_pred<double>(0.5)) << endl;	// 2
	cout << count_if2(vd.begin(), vd.end(), Less_pred<double>(-5.5)) << endl;	// 0
}	