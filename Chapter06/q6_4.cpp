#include "std_lib_facilities.h"

class Name_value{
public:
	Name_value() : name("Noname"), value(0) {}

	string name;
	int value;
};

bool is_overlap(string n, vector<Name_value> nv){
	for(int i = 0; i < nv.size(); ++i)
		if(nv[i].name == n)
			return true;

	return false;
}

int main(){
	vector<Name_value> nv;
	Name_value tmp;

	while(cin >> tmp.name >> tmp.value && tmp.name != "NoName" && tmp.value != 0){
		if(is_overlap(tmp.name, nv)){
			cout << "Error! (overlap)" << endl;
			exit(EXIT_FAILURE); 
		}

		nv.push_back(tmp);
	}

	for(int i = 0; i < nv.size(); ++i)
		cout << nv[i].name << " " << nv[i].value << endl;
}