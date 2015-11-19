#include "std_lib_facilities.h"

int main(){
	vector<char> randam(9);
	randam[0] = 'c';
	randam[1] = 'g';
	randam[2] = 'p';
	randam[3] = 'g';
	randam[4] = 'c';
	randam[5] = 'g';
	randam[6] = 'p';
	randam[7] = 'c';
	randam[8] = 'p';

	int index = 0;
	char input;
	while(cout << "じゃんけんぽんっ！（g: グー, c: チョキ, p: パー）: ", cin >> input){
		switch(input){
			case 'g':
				index += 1;
				break;

			case 'c':
				index += 2;
				break;

			case 'p':
				index += 5;
				break;

			default:
				continue;
		}

		if(index >= 8)
			index %= 9;

		switch(randam[index]){
			case 'g':
				cout << "グー！" << endl;

				switch(input){
					case 'g':
						cout << "あいこです。" << endl;
						break;
					case 'c':
						cout << "あなたの負けです。" << endl;
						break;
					case 'p':
						cout << "あなたの勝ちです。" << endl;
						break;
				}
				break;

			case 'c':
				cout << "チョキ！" << endl;

				switch(input){
					case 'c':
						cout << "あいこです。" << endl;
						break;
					case 'p':
						cout << "あなたの負けです。" << endl;
						break;
					case 'g':
						cout << "あなたの勝ちです。" << endl;
						break;
				}
				break;

			case 'p':
				cout << "パー！" << endl;

				switch(input){
					case 'p':
						cout << "あいこです。" << endl;
						break;
					case 'g':
						cout << "あなたの負けです。" << endl;
						break;
					case 'c':
						cout << "あなたの勝ちです。" << endl;
						break;
				}
				break;
		}
	}
}