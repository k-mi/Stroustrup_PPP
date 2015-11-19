// 平均温度と温度の中央値の計算

#include "std_lib_facilities.h"

int main(){
	vector<double> temps;		// 温度
	double temp;
	while(cin >> temp)			// 温度を読み取る
		temps.push_back(temp);	// vectorに追加する

	// 平均温度を計算する
	double sum = 0;
	for(int i = 0; i < temps.size(); ++i) sum += temps[i];
	cout << "Average temperature: " << sum / temps.size() << endl;

	// 中央値を計算する
	sort(temps.begin(), temps.end());	//tempsをbeginからendの順に並べ替える
	cout << "Median temperature: " << temps[temps.size() / 2] << endl;
}