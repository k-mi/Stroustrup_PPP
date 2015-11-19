#include "std_lib_facilities.h"

int main(){
	double temp = 0;
	double sum = 0;
	double high_temp = -1000;	// あり得ないほど小さい値に初期化する
	double low_temp = 1000;	// あり得ないほど大きな値に初期化する
	int no_of_temps = 0;

	while(cin >> temp){			// tempに読みとる
		++no_of_temps;
		sum += temp;
		if(temp > high_temp) high_temp = temp;	// 最高気温を割り出す
		if(temp < low_temp) low_temp = temp;	// 最低気温を割り出す
	}

	cout << "high temperature: " << high_temp << endl;
	cout << "low temperature: " << low_temp << endl;
	cout << "Average temperature; " << sum / no_of_temps << endl;
}