#include "std_lib_facilities.h"

void view_and(string str, int pos){
	int sum = 0;
	for(int i = pos+1; i < str.size(); ++i)
		sum += int(str[i] - '0');
	if(sum > 0)
		cout << " and ";
}

int main(){
	string str;
	cin >> str;

	int tmp;

	cout << str << " is ";
	switch(str.size()){
		case 4:
			tmp = int(str[str.size()-4] - '0');
			if(tmp != 0){
				cout << tmp << " thousand";
				view_and(str, str.size()-4);
			}
		case 3:
			tmp = int(str[str.size()-3] - '0');
			if(tmp == 1){
				cout << tmp << " handred";
				view_and(str, str.size()-3);
			}
			else if(tmp != 0){
				cout << tmp << " handreds";
				view_and(str, str.size()-3);
			}
		case 2:
			tmp = int(str[str.size()-2] - '0');
			if(tmp == 1){
				cout << tmp << " ten";
				view_and(str, str.size()-2);
			}
			else if(tmp != 0){
				cout << tmp << " tens";	
				view_and(str, str.size()-2);
			}
		case 1:
			tmp = int(str[str.size()-1] - '0');
			if(tmp == 1)
				cout << tmp << " one";
			else if(tmp != 0)
				cout << tmp << " ones";
			break;
		default:
			error("unexpected input");
	}
	cout << endl;		
}