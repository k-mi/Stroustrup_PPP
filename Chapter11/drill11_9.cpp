#include <iostream>
using namespace std;

// この条件では、有効数字を考えない場合fixedが最も正確な表現であるが、
// 有効数字を考えた場合はscientificとなる。
// generalはデフォルトでは全体で6桁までの表示を行うため、正確な表現ができていない。
int main(){
	const double num = 1234567.89;
	cout << num << "\tgeneral" << endl
		 << fixed << num << "\tfixed" << endl
		 << scientific << num << "\tscientific" << endl;
}