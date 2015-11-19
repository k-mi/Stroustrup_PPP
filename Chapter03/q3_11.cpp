#include "std_lib_facilities.h"

int main(){
	int penny, nickel, dime, quarter, half_dollar, dollar;

	// 入力
	cout << "How many pennies do you have? ";
	cin >> penny;
	cout << "How many nickels do you have? ";
	cin >> nickel;
	cout << "How many dimes do you have? ";
	cin >> dime;
	cout << "How many quarters do you have? ";
	cin >> quarter;
	cout << "How many half dollars do you have? ";
	cin >> half_dollar;
	cout << "How many dollars do you have? ";
	cin >> dollar;

	// 出力
	if(penny <= 1)
		cout << "You have " << penny << " penny." << endl;
	else
		cout << "You have " << penny << " pennies." << endl;

	if(nickel <= 1)
		cout << "You have " << nickel << " nickel." << endl;
	else
		cout << "You have " << nickel << " nickels." << endl;

	if(dime <= 1)
		cout << "You have " << dime << " dime." << endl;
	else
		cout << "You have " << dime << " dimes." << endl;

	if(quarter <= 1)
		cout << "You have " << quarter << " quarter." << endl;
	else
		cout << "You have " << quarter << " quarters." << endl;

	if(half_dollar <= 1)
		cout << "You have " << half_dollar << " half dollar." << endl;
	else
		cout << "You have " << half_dollar << " half dollars." << endl;

	if(dollar <= 1)
		cout << "You have " << dollar << " dollar." << endl;
	else
		cout << "You have " << dollar << " dollars." << endl;

	// 合計
	int sum = penny + nickel * 5 + dime * 10 + quarter * 25 + half_dollar * 50 + dollar * 100;
	
	if(sum < 100)
		cout << sum << " cent" << endl;
	else if(sum % 100 != 0)
		cout << sum / 100 << " doll " << sum - sum / 100 * 100 << " cent" << endl;
	else
		cout << sum / 100 << " doll" << endl;
}