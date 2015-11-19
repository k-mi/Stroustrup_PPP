#include "std_lib_facilities.h"

struct CalcResult{
	double max;
	double min;
	double ave;
	double med;
};

void calc(vector<double> v, CalcResult& cr){
	if(v.size() == 0)
		error("要素がありません");

	cr.max = cr.min = v[0];
	cr.ave = 0;

	for(int i = 1; i < v.size(); ++i){
		if(v[i] > cr.max)
			cr.max = v[i];
		if(v[i] < cr.min)
			cr.min = v[i];
		cr.ave += v[i];
	}

	cr.ave /= v.size();

	sort(v.begin(), v.end());
	if(v.size() % 2 == 0)
		cr.med = (v[(v.size()-1) / 2] + v[(v.size()-1) / 2 + 1]) / 2;
	else
		cr.med = v[(v.size()-1) / 2];
}

int main(){
	vector<double> v(10, 2.4);
	v[3] = -98.1;
	v[4] = 10;
	v[6] = 39.2;

	CalcResult cr;
	calc(v, cr);
	cout << "max: " << cr.max << endl;
	cout << "min: " << cr.min << endl;
	cout << "ave: " << cr.ave << endl;
	cout << "med: " << cr.med << endl;
}