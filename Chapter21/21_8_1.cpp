#include <iostream>
#include <locale>		// tolower
#include <vector>
#include <algorithm>	// sort
using namespace std;

// lowercase(x) < lowercase(y)であるか
struct No_case{
	bool operator()(const string& x, const string& y) const{
		for(int i = 0; i < x.length(); ++i){
			if(i == y.length()) return false;		// y < x（yの文字数のほうが少ない）
			char xx = tolower(x[i]);
			char yy = tolower(y[i]);
			if(xx < yy) return true;				// x < y
			if(yy < xx) return false;				// y < x
		}
		if(x.length() == y.length()) return false;	// x == y
		return true;								// x < y（xの文字数のほうが少ない）
	}
};

int main(){
	vector<string> v;
	v.push_back("Banana");
	v.push_back("Ab");
	v.push_back("apple");

	sort(v.begin(), v.end(), No_case());

	for(vector<string>::const_iterator p = v.begin(); p != v.end(); ++p)
		cout << *p << endl;
}