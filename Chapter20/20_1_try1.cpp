double* get_from_jack(int* count);	// Jackはdoubleを配列に格納し、
									// *countで要素の数を返す
vector<double>* get_from_jill();	// Jillはデータをvectorに設定する

void fct(){
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>& jill_data = get_from_jill();	// 参照を返す

	double* jack_high;	// jack_highは最も大きな値を持つ要素をポイントする
	double* jill_high;	// jill_highは最も大きな値を持つ要素をポイントする

	double h;			// 最も大きな要素

	if(jack_count > 0){
		jack_high = &jack_data[0];
		h = jack_data[0];
	}
	for(int i = 1; i < jack_count; ++i)
		if(h < jack_data[i]) {
			jack_high = &jack_data[i];	// 最も大きな要素のアドレスを保存
			h = jack_data[i];			// 「最も大きな要素」を更新
		}
	
	if(jill_data.size() > 0){
		jill_high = &jill_data[0];
		h = jill_data[0];
	}
	for(int i = 1; i < jill_data.size(); ++i)
		if(h < jill_data[i]){
			jill_high = &jill_data[i];	// 最も大きな要素のアドレスを保存
			h = jill_data[i];			// 「最も大きな要素」を更新
		}
	cout << "Jill's max: " << *jill_high
		 << "; Jack's max: " << *jack_high;

	delete[] jack_data;
	delete jill_data;S
}