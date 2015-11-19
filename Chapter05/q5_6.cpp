#include "std_lib_facilities.h"

// 摂氏(℃)を華氏（℉）に変換する
double ctof(double c){
	if(c < -273.15) 
		error("絶対零度下回る値です。");

	double f = 9.0/5 * c + 32;
	return f;
}

// 華氏（℉）を摂氏(℃)に変換する
double ftoc(double f){
	double c = (f - 32) * 5 / 9.0;

	if(c < -273.15) 
		error("絶対零度を下回る値です。");
	return c;
}

int main(){
	double temperature = 0;		// 気温
	char unit;					// 単位

	cout << "気温を入力してください。（c: 摂氏, f: 華氏）" << endl;

	while(cin >> temperature >> unit){
		switch(unit){
			case 'c':
				cout << " -> " << ctof(temperature) << "℉" << endl;
				break;
			case 'f':
				cout << " -> " << ftoc(temperature) << "℃" << endl;
				break;
			default:
				cout << "そのような単位は入力できません。" << endl;
				break;
		}		
	}
}