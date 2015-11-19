#include "std_lib_facilities.h"

int main(){
	const int FIGURE = 4;	// ゲームで使用する桁数
	vector<int> num;
	int n, bull, cow;
	char t;

	while(true){
		cout << "シード値を入力してください: ";
		cin >> n;
		srand(n);	// シード値を設定

		for(int i = 0; i < FIGURE; ++i){
			num.push_back(randint(10));	// 値を決定
			// cout << num[i] << endl;	// 答え
		}

		while(true){
			bull = cow = 0;

			// 判定
			for(int i = 0; i < FIGURE; ++i){
				cin >> t;

				if(num[i] == int(t - '0'))				// 桁が当たっている場合
					bull++;
				else{
					for(int j = 0; j < FIGURE; ++j){	// 数字が当たっている場合
						if(num[j] == int(t - '0')){
							cow++;
							break;					
						}
					}
				}
			}

			if(bull == 4){
				cout << "Clear!" << endl;
				break;
			}

			cout << bull << " bull and " << cow << " cow" << endl;		
		}		
	}
}