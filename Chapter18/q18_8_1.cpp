#include <iostream>
using namespace std;

bool is_palindrome(const string& s){
	string back;
	for(int i = s.size() - 1; i >= 0; --i)
		back.push_back(s[i]);

	for(int i = 0; i < s.size(); ++i)
		if(s[i] != back[i])
			return false;
	return true;
}

int main(){
	string s;
	while(cin >> s){
		cout << s << " is";
		if(!is_palindrome(s)) cout << " not";
		cout << " a palindrome\n";
	}
}