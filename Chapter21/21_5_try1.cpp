#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct Record{
	double unit_price;	// 単価
	int units;			// 販売された個数

	Record(double p, int u) : unit_price(p), units(u) { }
	// ...
};

double price(double v, const Record& r){
	return v + r.unit_price * r.units;
}

void f(const vector<Record>& vr){
	double total = accumulate(vr.begin(), vr.end(), 0.0, price);

	cout << total << endl;
}

int main(){
	vector<Record> vr(4, Record(256.4, 3));	// 256.4の商品を3個販売した記録が4つ

	f(vr);									// total: 3076.8
}