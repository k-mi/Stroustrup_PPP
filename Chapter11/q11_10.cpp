#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

bool is_punct(char c, const string& w){
	for(int i = 0; i < w.size(); ++i)
		if(c == w[i]) return true;
	return false;
}

// 通常のホワイトスペースとw内の文字で区切られた部分文字列を返す
vector<string> split(const string& s, const string& w){
	string tmp, ss = "";
	vector<string> vs;

	for(int i = 0; i < s.size(); ++i){
		if(is_punct(s[i], w))
			ss += ' ';
		else 
			ss += s[i];
	}

	istringstream ist(ss);
	while(ist >> tmp)
		vs.push_back(tmp);

	return vs;
}

int main(){
	string s;
	getline(cin, s);
	
	vector<string> v = split(s, ":;,.!?");
	for(int i = 0; i < v.size(); ++i)
		cout << v[i] << endl;
}