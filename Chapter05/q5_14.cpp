#include "std_lib_facilities.h"

int main(){
	vector<int> week(7, 0);

	string day;
	int value;

	// 入力
	while(cin >> day >> value){
		transform(day.begin(), day.end(), day.begin(), ::tolower);	// 小文字に変換

		if(day == "sun" || day == "sunday")
			week[0] += value;
		else if(day == "mon" || day == "monday")
			week[1] += value;
		else if(day == "tue" || day == "tuesday")
			week[2] += value;
		else if(day == "wed" || day == "wednesday")
			week[3] += value;		
		else if(day == "thu" || day == "thursday")
			week[4] += value;		
		else if(day == "fri" || day == "friday")
			week[5] += value;	
		else if(day == "sat" || day == "saturday")
			week[6] += value;
		else
			cout << "unknown day" << endl;		
	}

	cout << "Sun: " << week[0] << endl;
	cout << "Mon: " << week[1] << endl;
	cout << "Tue: " << week[2] << endl;
	cout << "Wed: " << week[3] << endl;
	cout << "Thu: " << week[4] << endl;
	cout << "Fri: " << week[5] << endl;
	cout << "Sat: " << week[6] << endl;
}