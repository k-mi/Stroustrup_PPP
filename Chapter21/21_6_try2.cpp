#include <iostream>
#include <unordered_map>
#include <numeric>		// inner_product
#include <functional>	// plus
using namespace std;

// 値を取得して掛ける
double weighted_value(const pair<string, double>& a, const pair<string, double>& b){
	return a.second * b.second;
}

int main(){
	// Dow Jones Industrial Indexes（シンボルと株価）
	unordered_map<string, double> dow_price;
	dow_price["MMM"] = 81.86;
	dow_price["AA"] = 34.69;
	dow_price["MO"] = 54.45;
	dow_price["AAPL"] = 113.78;

	unordered_map<string, double> dow_weight;	// Dow（シンボルと重み）
	dow_weight.insert(make_pair("MMM", 5.8549));
	dow_weight.insert(make_pair("AA", 2.4808));
	dow_weight.insert(make_pair("MO", 3.8940));
	dow_weight["AAPL"] = 6.2345;

	unordered_map<string, string> dow_name;	// Dow（シンボルと名前）
	dow_name["MMM"] = "3M Co.";
	dow_name["AA"] = "Alcoa Inc.";
	dow_name["MO"] = "Altria Group Inc.";
	dow_name["AAPL"] = "Apple Inc.";

	typedef unordered_map<string, double>::const_iterator Dow_iterator;
	// Dow Indexesの各企業の株価を書き出す
	for(Dow_iterator p = dow_price.begin(); p != dow_price.end(); ++p){
		const string& symbol = p->first;	// ティッカーシンボル
		cout << symbol << '\t'
			 << p->second << '\t'
			 << dow_name[symbol] << '\n';
	}

	double dji_index = 
		inner_product(dow_price.begin(), dow_price.end(),	// すべての企業
					  dow_weight.begin(),					// それらの重み
					  0.0,									// 初期値
					  plus<double>(),						// 加算
					  weighted_value);						// 値と重みの抽出
															// 乗算
	cout << dji_index << endl;
}