#include "std_lib_facilities.h"

int main(){
	cout << "Enter the name of the person you want to write to ";
	string first_name;
	cin >> first_name;
	
	cout << "Enter the name of a friend: ";
	string friend_name;
	cin >> friend_name;

	cout << "Enter " << friend_name << "'s' gender(m: male, f: female): ";
	char friend_gender = 0;
	cin >> friend_gender;

	cout << "Enter " << first_name << "'s age: ";
	int age;
	cin >> age;

	if(age < 0 || age >= 110)
		simple_error("you're kidding!");

	cout << "\n\n";

	cout << "Dear " << first_name << ",\n\n";
	cout << "     How are you? I am fine. I miss you.\n";

	if(friend_gender == 'm')
		cout << "If you see " << friend_name << " please ask him to call me.\n";
	if(friend_gender == 'f')
		cout << "If you see " << friend_name << " please ask her to call me.\n";

	cout << "I hear you just had a birthday and you are " << age << "years old.\n";

	if(age < 12)
		cout << "Next year you will be " << age + 1 << "." << endl;
	else if(age < 17)
		cout << "Neat year you will be able to vote." << endl;
	else
		cout << "I hope you are enjoying retirement." << endl;

	cout << "\nYours sincerely\n\nMizuki\n\n";
}