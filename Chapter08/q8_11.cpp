#include "std_lib_facilities.h"

double maxv(const vector<double>& v){
	double max = v[0];
	for(int i = 1; i < v.size(); ++i)
		if(v[i] > max)
			max = v[i];

	return max;
}

int main(){
	vector<double> v(10, 2.4);
	v[3] = -98.1;
	v[6] = 39.2;

	cout << "max: " << maxv(v) << endl;
}