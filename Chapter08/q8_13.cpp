#include "std_lib_facilities.h"

void print_until_s(vector<string> v, string quit){
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == quit) return;
		cout << v[i] << '\n';
	}
}

void print_until_ss(const vector<string>& v, string quit){
	bool once = false;
	for(int i = 0; i < v.size(); ++i){
		if(v[i] == quit){
			if(once) return;
			once = true;
		}
		cout << v[i] << endl;
	}
}

int main(){
	vector<string> v(10, "Apple");
	v[3] = v[8] = "quit";

	print_until_s(v, "quit");
	cout << endl;
	print_until_ss(v, "quit");
}