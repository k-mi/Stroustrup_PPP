#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

struct Reading{			// 計測値（温度）
	int hour;			// 午後0時からの時刻[0:23]
	double temprature;	// 華氏
	Reading(int h, double t) : hour(h), temprature(t) { }
};

int main(){
	cout << "Please enter input file name: ";
	string name;
	cin >> name;
	ifstream ist(name.c_str());	// istはnameで与えられたファイル名により読み取る
	if(!ist) throw runtime_error("can't open input file " + name);

	cout << "Please enter output file name: ";
	cin >> name;
	ofstream ost(name.c_str());
	if(!ost) throw runtime_error("can't open output file " + name);

	vector<Reading> temps;	// 計測値を格納する
	int hour;
	double temprature;
	while(ist >> hour >> temprature){
		if(hour < 0 || 23 < hour) throw runtime_error("hour out of range");
		temps.push_back(Reading(hour, temprature));
	}

	for(int i = 0; i < temps.size(); ++i){
		ost << '(' << temps[i].hour << ',' << temps[i].temprature << ')' << endl;
	}
}