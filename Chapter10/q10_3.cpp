// temp_stats.cpp

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
using namespace std;

struct Reading{			// 計測値（温度）
	int hour;			// 午後0時からの時刻[0:23]
	double temprature;	// 気温
	Reading(int h, double t) : hour(h), temprature(t) { }
};

Reading get_reading(istream& is){
	while(!is.eof()){
		int h;
		double t;
		char c;
		
		is >> h >> t;
		if(is.fail() || h < 0 || 23 < h){
			is.clear();
			is >> c;
			continue;
		}

		return Reading(h, t);
	}
	return Reading(-1, 0);	// EOFの場合hourを-1に設定する
}

double average(const vector<Reading>& r){
	double sum = 0;
	for(int i = 0; i < r.size(); ++i)
		sum += r[i].temprature;
	return sum / r.size();
}

double median(const vector<Reading>& r){
	vector<double> d;
	for(int i = 0; i < r.size(); ++i)
		d.push_back(r[i].temprature);
	sort(d.begin(), d.end());

	if(d.size() % 2 == 0)
		return (d[d.size() / 2 - 1] + d[d.size() / 2]) / 2;
	else
		return d[d.size() / 2];
}

int main(){
	string filename;
	vector<Reading> temps;

	cout << "読み取るデータファイルの名前を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	Reading reading = get_reading(ifs);
	while(reading.hour != -1){
		temps.push_back(reading);
		reading = get_reading(ifs);
	}

	cout << "平均温度: " << average(temps) << endl;
	cout << "中央温度: " << median(temps) << endl;
}