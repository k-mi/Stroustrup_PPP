#include "std_lib_facilities.h"
#include <limits>

int main(){
	vector<double> distance;
	double input, sum = 0;
	double min = numeric_limits<double>::max(), max = numeric_limits<double>::min();

	while(cin >> input){
		distance.push_back(input);

		if(min > input)
			min = input;
		if(max < input)
			max = input;
		sum += input;
	}

	cout << "総距離: " << sum << endl;
	cout << "最短距離: " << min << endl;
	cout << "最長距離: " << max << endl;
	cout << "平均距離: " << sum / distance.size() << endl; 
}