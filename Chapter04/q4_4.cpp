#include "std_lib_facilities.h"

int main(){
	int min = 1, max = 100, mid = (max + min) / 2;
	char answer;

	while(max - min > 1){
		cout << "あなたが考えている数字は " << (max + min) / 2 << " より小さいですか？（y or n）: ";
		cin >> answer;
		
		if(answer == 'y')
			max = (max + min) / 2 - 1;
		else if(answer == 'n')
			min = (max + min) / 2;
	}

	cout << "あなたが考えている数字は " << max << " より小さいですか？（y or n）: ";
	cin >> answer;
	
	if(answer == 'y')
		cout << "あなたが考えている数字は " << min << " ですね！" << endl;
	else if(answer == 'n')
		cout << "あなたが考えている数字は " << max << " ですね！" << endl;
}