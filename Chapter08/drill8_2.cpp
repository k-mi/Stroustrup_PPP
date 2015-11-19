#include <iostream>
using namespace std;

void swap_v(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int& a, int& b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_cr(const int& a, const int& b){
	int temp;
	temp = a;
	// a = b;
	// b = temp;	
}

int main(){
	int x = 7;
	int y = 9;
	swap_v(x, y);		// 交換されない
	swap_v(7, 9);		// 交換されない
	swap_r(x, y);		// 交換
	//swap_r(7, 9);		// エラー: literal
	//swap_cr(x, y);	// エラー: const
	//swap_cr(7, 9);	// エラー: const

	const int cx = 7;
	const int cy = 9;
	swap_v(x, y);		// 交換されない
	swap_v(7, 9);		// 交換されない
	//swap_r(x, y);		// エラー: 参照先の変数のconst
	//swap_r(7, 9);		// エラー: literal
	//swap_cr(x, y);	// エラー: const
	//swap_cr(7, 9);	// エラー: const

	double dx = 7.7;
	double dy = 9.9;
	swap_v(dx, dy);		// 交換されない intにキャスト 
	swap_v(7.7, 9.9);	// 交換されない intにキャスト 
	//swap_r(dx, dy);	// エラー: 参照先の型が異なる
	//swap_r(7.7, 9.9);	// エラー: literal
	//swap_cr(dx, dy);	// エラー: const
	//swap_cr(7.7, 9.9);// エラー: const
}