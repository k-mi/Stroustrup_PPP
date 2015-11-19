// 平均温度と温度の中央値の計算

#include "std_lib_facilities.h"

// 平均温度を計算する
double average(vector<double> temps){
	double sum = 0;
	for(int i = 0; i < temps.size(); ++i) 
		sum += temps[i];
	return sum / temps.size();
}

// 中央値を計算する
double median(vector<double> temps){
	sort(temps.begin(), temps.end());	//tempsをbeginからendの順に並べ替える
	if(temps.size() % 2 == 1)
		return temps[temps.size() / 2];
	else
		return (temps[temps.size() / 2 - 1] + temps[temps.size() / 2]) / 2;
}

int main(){
	vector<double> temps;		// 温度
	double temp;

	// 入力
	while(cin >> temp)			// 温度を読み取る
		temps.push_back(temp);	// vectorに追加する

	// 出力
	cout << "Average temperature: " << average(temps) << endl;
	cout << "Median temperature: " << median(temps) << endl;				
}