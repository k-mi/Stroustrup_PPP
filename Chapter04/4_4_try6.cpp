#include "std_lib_facilities.h"

int main(){
	vector<string> words;
	string tmp;
	string disliked = "Broccoli";

	while(cin >> tmp)
		words.push_back(tmp);

	for(int i = 0; i < words.size(); ++i)
		if(words[i] != disliked)
			cout << words[i] << endl;
		else
			cout << "BLEEP\a" << endl;
}