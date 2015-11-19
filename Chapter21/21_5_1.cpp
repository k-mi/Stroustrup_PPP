#include <iostream>
#include <vector>
#include <list>
//#include <numeric>
using namespace std;

// 2つのvectorを掛け合わせる（スカラーを生成する）方法
template<class In, class In2, class T> 
T inner_product(In first, In last, In2 first2, T init){
	while(first != last){
		init = init + (*first) * (*first2);	// 要素同士を掛け合わせる
		++first;
		++first2;
	}
	return init;
}

int main(){
	// Dow Jones Industrial Indexesの計算
	vector<double> dow_price;	// 各企業の株価
	dow_price.push_back(81.86);
	dow_price.push_back(34.69);
	dow_price.push_back(54.45);
	// ...

	list<double> dow_weight;	// 各企業の指数の重み
	dow_weight.push_back(5.8549);
	dow_weight.push_back(2.4808);
	dow_weight.push_back(3.8940);
	// ...

	double dji_index = inner_product(
		dow_price.begin(), dow_price.end(), dow_weight.begin(), 0.0);

	cout << "DJI value " << dji_index << endl;
}