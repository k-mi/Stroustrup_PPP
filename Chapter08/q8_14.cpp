#include "std_lib_facilities.h"

vector<int> stringsize(const vector<string>& v){
	vector<int> ret;
	for(int i = 0; i < v.size(); ++i)
		ret.push_back(v[i].size());

	return ret;
}

void minmaxstring(const vector<string>& v, string& min, string& max){
	int minsize = v[0].size();
	int maxsize = v[0].size();
	min = max = v[0];
	for(int i = 1; i < v.size(); ++i){
		if(v[i].size() < minsize){
			minsize = v[i].size();
			min = v[i];
		}
		if(v[i].size() > maxsize){
			maxsize = v[i].size();
			max = v[i];
		}
	}
}

void dicstring(vector<string> v, string& first, string& last){
	sort(v.begin(), v.end());
	first = v[0];
	last = v[v.size() - 1];
}

int main(){
	vector<string> strings(10, "Apple");
	strings[5] = "Banana";
	strings[8] = "Cat";

	string min, max, first, last;
	stringsize(strings);
	minmaxstring(strings, min, max);
	dicstring(strings, first, last);
	cout << "min: " << min << endl;
	cout << "max: " << max << endl;
	cout << "first: " << first << endl;
	cout << "last: " << last << endl;
}