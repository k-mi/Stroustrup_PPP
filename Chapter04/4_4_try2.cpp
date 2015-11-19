// 円、ユーロ、ポンドからドルへの変換
// サフィックスの'y'と'e'と'p'は入力の単位を表す
// その他のサフィックスはエラーになる

#include "std_lib_facilities.h"

int main(){
	const double yen_per_dollar = 123.122384;	// 1ドルあたりの円
	const double euro_per_dollar = 0.901087613;	// 1ドルあたりのユーロ
	const double pond_per_dollar = 0.642549637;	// 1ドルあたりのポンド

	double money = 1;					// お金
	char unit = ' ';					// スペースは単位ではない
	cout << "Please enter dollars followed by a unit (y or e or p):\n";
	cin >> money >> unit;

	switch(unit){
		case 'y':
			cout << money << "yen == " << money / yen_per_dollar << "dollar\n";
			break;
		case 'e':
			cout << money << "euro == " << money / euro_per_dollar << "dollar\n";
			break;
		case 'p':
			cout << money << "pond == " << money / pond_per_dollar << "dollar\n";
			break;
		default:
			cout << "Sorry, I don't know a unit called '" << unit << "'\n";	
			break;
	}		
}