double* get_from_jack(int* count);	// Jackはdoubleを配列に格納し、
									// *countで要素の数を返す
vector<double>* get_from_jill();	// Jillはデータをvectorに設定する

// 最も大きな値を持つ[first:last)の範囲内の要素へのイテレータを返す
template<class Iterator> 
Iterator high(Iterator first, Iterator last){
	Iterator high = first;
	for(Iterator p = first; p != last; ++p)
		if(*high < *p) high = p;
	return high;
}

void fct(){
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);
	vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[0] + v.size());
	cout << "Jill's max: " << *jill_high << "; Jack's max: " << *jack_high;

	//...

	delete[] jack_data;
	delete jill_data;
}