#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Jackはdoubleを配列に格納し、*countで要素の数を返す
double* get_from_jack(int* count){
	string filename = "q20_2_input_jack.txt";
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
	string filename = "q20_2_input_jill.txt";
	ifstream ifs(filename);

	vector<double>* p = new vector<double>;
	double tmp;
	while(ifs >> tmp)
		p->push_back(tmp);

	return p;
}

// 最も大きな値を持つ[first,last)の範囲内の要素へのポインタを返す
double* high(double* first, double* last){
	if(first == last) return last;
	double h = *first;				// 最初の要素とそのポインタで初期化する
	double* high = first;
	for(double* p = first + 1; p != last; ++p)	// 次の要素から比較を開始
		if(h < *p) { high = p; h = *p; }		
	return high;
}

void fct(){
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();

	double* jack_high = high(jack_data, jack_data + jack_count);

	vector<double>& v = *jill_data;
	double* jill_high = high(&v[0], &v[v.size() - 1]);

	cout << "Jill's max: " << *jill_high << "; Jack's max: " << *jack_high << endl;

	delete[] jack_data;
	delete jill_data;
}

int main(){
	fct();
}