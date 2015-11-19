// 10_11_1.cppよりprint_year()部分のみを抽出

void print_year(ostream& os, const Year& y){
	for(int i = 0; i < y.month.size(); ++i){		// Month
		const Month& m = y.month[i];
		if(m.month != not_a_month){
			os << "{ month " << int_to_month(m.month) << ' ';
			for(int j = 0; j < m.day.size(); ++j){	// Day
				const Day& d = m.day[j];
				for(int k = 0; k < d.hour.size(); ++k){
					if(d.hour[k] != not_a_reading){	// Hour
						os << "( " << j << ' ' << k << ' ' << d.hour[k] << " )";				
					}
				}
			}
			os << '}';	
		}		
	}
}