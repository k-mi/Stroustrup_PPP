// store_temps.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

struct Reading{			// 計測値（温度）
	int hour;			// 午後0時からの時刻[0:23]
	double temprature;	// 気温（華氏）
	Reading(int h, double t) : hour(h), temprature(t) { }
};

Reading get_reading(){
	int hour;
	double temprature;
	char unit, c;

	while(true){
		cin >> hour >> temprature >> unit;

		if(cin.fail()){
			cin.clear();
			cin >> c;
			continue;
		}
		if(hour < 0 || 23 < hour) continue;
		if(unit != 'c' && unit != 'f') continue;
		double t = unit == 'f' ? temprature : (1.8 * temprature + 32);
		return Reading(hour, t);
	}
}

int main(){
	string filename;
	vector<Reading> temps;

	cout << "作成するデータファイルの名前を入力してください。 > ";
	cin >> filename;
	ofstream ofs(filename.c_str());
	if(!ofs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	for(int i = 0; i < 50; ++i){
		cout << "時間と温度を入力してください。(" << i+1 << "件目) > ";
		temps.push_back(get_reading());
	}

	for(int i = 0; i < temps.size(); ++i)
		ofs << temps[i].hour << ' ' << temps[i].temprature << endl;
}