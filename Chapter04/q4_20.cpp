#include "std_lib_facilities.h"

bool is_overlap(string n, vector<string> name){
	for(int i = 0; i < name.size(); ++i)
		if(name[i] == n)
			return true;

	return false;
}

int find(string n, vector<string> name){
	for(int i = 0; i < name.size(); ++i)
		if(name[i] == n)
			return i;

	return -1;	
}

int main(){
	vector<string> name;
	vector<int> scores;
	string n;
	int s, index;

	while(cin >> n >> s && n != "NoName" && s != 0){
		if(is_overlap(n, name)){
			cout << "Error! (overlap)" << endl;
			exit(EXIT_FAILURE); 
		}

		name.push_back(n);
		scores.push_back(s);
	}

	while(cin >> n){
		index = find(n, name);
		if(index != -1)
			cout << scores[index] << endl;
		else
			cout << "name not found" << endl;		
	}

}