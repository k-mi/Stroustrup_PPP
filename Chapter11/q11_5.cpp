#include <iostream>
#include <cctype>
using namespace std;

int main(){
	string line, convert_str;
	while(getline(cin, line)){
		convert_str = "";
		for(int i = 0; i < line.size(); ++i){
			if(ispunct(line[i])) 
				convert_str += ' ';
			else	
				convert_str += line[i];
		}
		cout << convert_str << endl;
	}	
}