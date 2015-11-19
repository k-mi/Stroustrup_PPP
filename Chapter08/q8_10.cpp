#include "std_lib_facilities.h"

double sum(const vector<double>& price, const vector<double>& weight){
	double sum = 0;

	for(int i = 0; i < weight.size() && i < price.size(); ++i)
		sum += price[i] * weight[i];

	return sum;
}

int main(){
	vector<double> price;
	vector<double> weight;

	price.push_back(50);
	price.push_back(26.8);
	weight.push_back(5);
	weight.push_back(3);

	cout << "sum: " << sum(price, weight) << endl;
}