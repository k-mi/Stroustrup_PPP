#include "std_lib_facilities.h"

int main(){
	vector<double> temps;		// 気温
	double temp = 0;
	double sum = 0;
	double high_temp = 0;
	double low_temp = 0;

	while(cin >> temp)			// 値を読み取ってtempに代入する
		temps.push_back(temp);

	for(int i = 0; i < temps.size(); ++i){
		if(temps[i] > high_temp) high_temp = temps[i];	// 最高気温を割り出す
		if(temps[i] < low_temp) low_temp = temps[i];	// 最低気温を割り出す
		sum += temps[i];								// 合計を求める
	}

	cout << "high temperature: " << high_temp << endl;
	cout << "low temperature: " << low_temp << endl;
	cout << "Average temperature; " << sum / temps.size() << endl;
}