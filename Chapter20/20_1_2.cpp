double* get_from_jack(int* count);	// Jackはdoubleを配列に格納し、
									// *countで要素の数を返す
vector<double>* get_from_jill();	// Jillはデータをvectorに設定する

void fct(){
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	// ...

	double* jack_high;	// jack_highは最も大きな値を持つ要素をポイントする
	double* jill_high;	// jill_highは最も大きな値を持つ要素をポイントする

	for(int i = 0; i < jack_count; ++i)
		if(h < jack_data[i]) {
			jack_high = &jack_data[i];	// 最も大きな要素のアドレスを保存
			h = jack_data[i];			// 「最も大きな要素」を更新
		}

	vector<double>& v = *jill_data;
	for(int i = 0; i < v.size(); ++i)
		if(h < v[i]){
			jill_high = &v[i];			// 最も大きな要素のアドレスを保存
			h = v[i];					// 「最も大きな要素」を更新
		}
	cout << "Jill's max: " << *jill_high
		 << "; Jack's max: " << *jack_high;

	delete[] jack_data;
	delete jill_data;
}