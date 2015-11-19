#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Jackはdoubleを配列に格納し、*countで要素の数を返す
double* get_from_jack(int* count){
	string filename = "jack.txt";
	ifstream ifs(filename);

	*count = 0;		// 要素の数
	int space = 8;	// 要素の数 + 空きスロットの数
	double* elem = new double[8];

	double tmp;
	while(ifs >> tmp){
		if(*count == space){	// 空きスロット数が無い場合
			double* p = new double[space * 2];
			for(int i = 0; i < *count; ++i)
				p[i] = elem[i];
			delete[] elem;
			elem = p;
			space *= 2;
		}
		elem[(*count)++] = tmp;
	}
	return elem;
}

// Jillはデータをvectorに設定する
vector<double>* get_from_jill(){
	string filename = "jill.txt";
	ifstream ifs(filename);

	vector<double>* p = new vector<double>;
	double tmp;
	while(ifs >> tmp)
		p->push_back(tmp);

	return p;
}

// vector<double>を使用して最大値を求める
double* high_vector(vector<double>& v){
	if(v.size() == 0) return nullptr;	// 空のvectorであればヌルポインタを返す		
	double* high = &v[0];
	for(int i = 1; i < v.size(); ++i)
		if(*high < v[i]) high = &v[i];
	return high;
}

// 配列を使用して最大値を求める
double* high_array(double d[], int n){
	if(n <= 0) return nullptr;
	double* high = &d[0];
	for(int i = 1; i < n; ++i)
		if(*high < d[i]) high = &d[i];
	return high;		
}

// ポインタを使用して最大値を求める
// 最も大きな値を持つ[first,last)の範囲内の要素へのポインタを返す
double* high_pointer(double* first, double* last){
	if(first == last) return last;
	double* high = first;
	for(double* p = first + 1; p != last; ++p)	// 次の要素から比較を開始
		if(*high < *p) high = p;
	return high;
}

void fct(){
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	// vector
	vector<double> jack_data_vec;				// jack_dataをvectorにコピー
	for(int i = 0; i < jack_count; ++i) 
		jack_data_vec.push_back(jack_data[i]);
	double* jack_high = high_vector(jack_data_vec);
	double* jill_high = high_vector(*jill_data);
	cout << "[vector] Jill's max: " << *jill_high << "; Jack's max: " << *jack_high << endl;

	// 配列
	double jill_data_array[jill_data->size()];	// jill_dataを配列にコピー
	for(int i = 0; i < jill_data->size(); ++i) 
		jill_data_array[i] = (*jill_data)[i];
	jack_high = high_array(jack_data, jack_count);
	jill_high = high_array(jill_data_array, jill_data->size());
	cout << "[array] Jill's max: " << *jill_high << "; Jack's max: " << *jack_high << endl;

	// ポインタ
	jack_high = high_pointer(jack_data, jack_data + jack_count);
	vector<double>& v = *jill_data;
	jill_high = high_pointer(&v[0], &v[v.size() - 1]);
	cout << "[pointer] Jill's max: " << *jill_high << "; Jack's max: " << *jack_high << endl;

	delete[] jack_data;
	delete jill_data;
}

int main(){
	fct();
}