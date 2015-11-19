#include "std_lib_facilities.h"

// 摂氏を華氏に変換する
double ctok(double c){
	double k = c * 1.8 + 32;
	return k;
}

int main(){
	double c = 0;			// 入力変数を宣言する
	cin >> c;				// 気温値を入力変数に取り出す
	double k = ctok(c);		// 気温値を変換する
	cout << k << endl;		// 気温値を出力する
}

/* エラー
 * 5: kの型がintになっている
 * 5: 摂氏と華氏の換算式が誤っている	
 * 6: 戻り値の変数が予約語（int）
 * 6: 文末にセミコロンがない
 * 11: 入力先の変数が誤っている
 * 12: int型の変数ではなく、文字列リテラルを渡している
 * 13: coutが大文字になっている
 */