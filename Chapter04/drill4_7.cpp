#include "std_lib_facilities.h"
#include <limits>

int main(){
	double val, min = numeric_limits<double>::max(), max = numeric_limits<double>::min();
	const double m_cm = 100;
	const double in_cm = 2.54;
	const double ft_cm = 12 * in_cm;
	string unit = "";

	while(cin >> val >> unit){	
		if(unit == "cm"){
			cout << val << "cm" << endl;
		}
		else if(unit == "m"){
			cout << val << "m == " << val * m_cm << "cm" << endl;
			val *= m_cm;
		}
		else if(unit == "in"){
			cout << val << "in == " << val * in_cm << "cm" << endl;
			val *= in_cm;
		}		
		else if(unit == "ft"){
			cout << val << "ft == " << val * ft_cm << "cm" << endl;
			val *= ft_cm;
		}

		if(val < min){
			cout << "the smallest so far" << endl;
			min = val;
		}
		if(val > max){
			cout << "the largest so far" << endl;
			max = val;			
		}
	}
}