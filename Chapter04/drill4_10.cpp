#include "std_lib_facilities.h"
#include <limits>

int main(){
	double val, sum = 0;
	double min = numeric_limits<double>::max(), max = numeric_limits<double>::min();
	const double m_cm = 100;
	const double in_cm = 2.54;
	const double ft_in = 12;
	int count = 0;
	string unit = "";
	vector<double> vals;

	while(cin >> val >> unit){	
		if(unit == "cm"){
			cout << val << "cm == " << val / m_cm << "m" << endl;
			val /= m_cm;
		}
		else if(unit == "m"){
			cout << val << "m" << endl;
		}
		else if(unit == "in"){
			cout << val << "in == " << val * in_cm / m_cm << "m" << endl;
			val *= in_cm / m_cm ;
		}		
		else if(unit == "ft"){
			cout << val << "ft == " << val * ft_in * in_cm / m_cm << "m" << endl;
			val *= ft_in * in_cm / m_cm;
		}
		else{
			cout << "Sorry, I don't know a unit called \"" << unit << "\"" << endl;
			continue;
		}

		count++;
		sum += val;
		vals.push_back(val);

		if(val < min){
			cout << "the smallest so far" << endl;
			min = val;
		}
		if(val > max){
			cout << "the largest so far" << endl;
			max = val;			
		}
	}

	// 出力
	for(int i = 0; i < vals.size(); ++i)
		cout << vals[i] << "m" << endl;

	cout << "最小値: " << min << "m" << endl;
	cout << "最大値: " << max << "m" << endl;
	cout << "値の数: " << count << endl;
	cout << "値の合計: " << sum << "m" << endl;
}