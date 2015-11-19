#include "std_lib_facilities.h"

int main(){
	const int FIGURE = 4;	// ゲームで使用する桁
	vector<char> num(FIGURE);
	num[0] = '1';
	num[1] = '2';
	num[2] = '3';
	num[3] = '4';

	int bull, cow;
	char t;

	while(1){
		bull = cow = 0;

		// 判定
		for(int i = 0; i < FIGURE; ++i){
			cin >> t;

			if(num[i] == t)					// 桁が当たっている場合
				bull++;
			else{
				for(int j = 0; j < FIGURE; ++j)	// 数字が当たっている場合
					if(num[j] == t)
						cow++;					
			}
		}

		if(bull == 4){
			cout << "Clear!" << endl;
			break;
		}

		cout << bull << " bull and " << cow << " cow" << endl;		
	}

}