// store_temps.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

struct Reading{			// 計測値（温度）
	int hour;			// 午後0時からの時刻[0:23]
	double temprature;	// 気温
	Reading(int h, double t) : hour(h), temprature(t) { }
};

Reading get_reading(){
	int h;
	double t;
	char c;

	while(true){
		cin >> h >> t;

		if(cin.fail()){
			cin.clear();
			cin >> c;
		}
		else if(h >= 0 || 23 >= h)
			return Reading(h, t);
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