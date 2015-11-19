#include <iostream>
#include <map>
using namespace std;

int main(){
	// Dow Jones Industrial Indexes（シンボルと株価）
	map<string, double> dow_price;
	dow_price["MMM"] = 81.86;
	dow_price["AA"] = 34.69;
	dow_price["MO"] = 54.45;

	map<string, double> dow_weight;	// Dow（シンボルと重み）
	dow_weight.insert(make_pair("MMM", 5.8549));
	dow_weight.insert(make_pair("AA", 2.4808));
	dow_weight.insert(make_pair("MO", 3.8940));

	map<string, string> dow_name;	// Dow（シンボルと名前）
	dow_name["MMM"] = "3M Co.";
	dow_name["AA"] = "Alcoa Inc.";
	dow_name["MO"] = "Altria Group Inc.";


	double alcoa_price = dow_price["AA"];	// mapから値を読み取る
	double altria_price = dow_price["MO"];
	cout << alcoa_price << " " << altria_price << endl;

	if(dow_price.find("INTC") != dow_price.end())	// mapでエントリを検索する
		cout << "Intel is in the Dow\n";

	typedef map<string, double>::const_iterator Dow_iterator;

	// Dow Indexesの各企業の株価を書き出す
	for(Dow_iterator p = dow_price.begin(); p != dow_price.end(); ++p){
		const string& symbol = p->first;	// ティッカーシンボル
		cout << symbol << '\t'
			 << p->second << '\t'
			 << dow_name[symbol] << '\n';
	}
}