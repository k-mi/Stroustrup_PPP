#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>		// istream_iterator, ostream_iterator
#include <algorithm>	// copy
using namespace std;

int main(){
	string from, to;
	cin >> from >> to;						// コピー元とコピー先ｎファイル名を取得する

	ifstream is(from.c_str());				// 入力ストリームを開く
	ofstream os(to.c_str());				// 出力ストリームを開く

	istream_iterator<string> ii(is);		// ストリーム用の入力イテレータを作成する
	istream_iterator<string> eos;			// 入力の終端を表す
	ostream_iterator<string> oo(os, "\n");	// ストリーム用の出力イテレータを作成する	

	vector<string> b(ii, eos);				// bは入力によって初期化されるvector
	sort(b.begin(), b.end());				// バッファをソートする
	unique_copy(b.begin(), b.end(), oo);	// バッファを出力にコピーする（重複しない）
}