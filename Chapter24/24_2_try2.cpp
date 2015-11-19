#include <iostream>
using namespace std;

void f(int i, double fpd){
	char c = i;			// 実際問題として、charは非常に小さい整数である
	cout << "c: " << (int)c << endl;

	short s = i;		// 注意: intはshort intに収まらないことがある
	cout << "s: " << s << endl;

	i = i + i;			// iが最も大きいintだった場合はどうなるか
	cout << "i: " << i << endl;

	long lg = i * i;	// 注意: longはintよりも大きくないことがある
	cout << "lg: " << lg << endl;

	float fps = fpd;	// 注意: 大きなdoubleはfloatに収まらないことがある
	cout << "fps: " << fps << endl;

	i = fpd;			// 切り捨て: たとえば5.7 -> 5
	cout << "i: " << i << endl;

	fps = i;			// (intの値が非常に大きい場合は)精度を失う可能性がある
	cout << "fps: " << fps << endl;
}

void g(){
	char ch = 0;
	for(int i = 0; i < 500; ++i)
		cout << int(ch++) << '\t';
}

int main(){
	int i;
	double fpd;
	while(cin >> i >> fpd)
		f(i, fpd);

	g();
}