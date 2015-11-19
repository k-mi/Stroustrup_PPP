#include "std_lib_facilities.h"

int main(){
	double distance;

	cout << "距離をマイルで入力してください。" << endl;
	cin >> distance;
	cout << distance << "[mile] = " << distance * 1.690 << "[km]" << endl;
}