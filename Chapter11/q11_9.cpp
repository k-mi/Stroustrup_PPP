#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(const string& s){
	string tmp;
	vector<string> vs;
	istringstream ist(s);

	while(ist >> tmp)
		vs.push_back(tmp);

	return vs;
}

int main(){
	string s;
	getline(cin, s);
	
	vector<string> v = split(s);
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << endl;
}