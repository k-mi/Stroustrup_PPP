#include "std_lib_facilities.h"

bool is_overlap(string n, vector<string> name){
	for(int i = 0; i < name.size(); ++i)
		if(name[i] == n)
			return true;

	return false;
}

int main(){
	vector<string> name;
	vector<int> scores;
	string n;
	int s, index;
	bool view;

	while(cin >> n >> s && n != "NoName" && s != 0){
		if(is_overlap(n, name)){
			cout << "Error! (overlap)" << endl;
			exit(EXIT_FAILURE); 
		}

		name.push_back(n);
		scores.push_back(s);
	}

	while(cin >> s){
		view = false;
		for(index = 0; index < name.size(); ++index){
			if(scores[index] == s){
				view = true;
				cout << name[index] << endl;
			}
		}
		if(view == false)
			cout << "score not found" << endl;
	}
}