#include "std_lib_facilities.h"

int main(){
	struct Coin{
		string singular_name;
		string plural_name;
		int val;
	};

	Coin coin[6];

	coin[0].singular_name = "penny";
	coin[1].singular_name = "nickel";
	coin[2].singular_name = "dime";
	coin[3].singular_name = "quarter";
	coin[4].singular_name = "half dollar";
	coin[5].singular_name = "dollar";
	coin[0].plural_name = "pennies";
	for(int i = 1; i < 6; ++i)
		coin[i].plural_name = coin[i].singular_name + "s";

	// 入力
	for(int i = 0; i < 6; ++i){
		cout << "How many " << coin[i].plural_name << " do you have? ";
		cin >> coin[i].val;
	}

	// 出力
	for(int i = 0; i < 6; ++i){
		cout << "You have " << coin[i].val << " ";
		if(coin[i].val <= 1)
			cout << coin[i].singular_name << endl;
		else
			cout << coin[i].plural_name << endl;		
	}	

	int sum = coin[0].val + coin[1].val * 5 + coin[2].val * 10 +
			  coin[3].val * 25 + coin[4].val * 50 + coin[5].val * 100;
	if(sum < 100)
		cout << sum << " cent" << endl;
	else if(sum % 100 != 0)
		cout << sum / 100 << " doll " << sum - sum / 100 * 100 << " cent" << endl;
	else
		cout << sum / 100 << " doll" << endl;
}