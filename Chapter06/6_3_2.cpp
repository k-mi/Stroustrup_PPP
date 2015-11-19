#include "std_lib_facilities.h"

int main(){
	cout << "Please enter expression (we can handle +, -, *, and /): ";
	cout << "add an x to and expression (e.g., 1+2*3;): ";
	int lval = 0;
	int rval;
	char op;
	cin >> lval;		// 左端のオペランドを読み取る
	if(!cin) error("no first operand");
	while(cin >> op){	// 演算子と右オペランドの読み取りを繰り返す
		switch(op){		// 追加部分（もとのままではgccで動作せず）
			case '+': case '-': case '*': case '/':
				cin >> rval;
				if(!cin) error("no second operand");
				break;	
		}

		switch(op){
			case '+':
				lval += rval;	// 加算: lval = lval + rval;
				break;
			case '-':
				lval -= rval;	// 減算: lval = lval - rval;
				break;
			case '*':
				lval *= rval;	// 乗算: lval = lval * rval;
				break;
			case '/':
				lval /= rval;	// 除算: lval = lval / rval;
				break;
			default:			// 他に演算子はない: 結果を出力する
				cout << "Result: " << lval << '\n';
				keep_window_open();
				return 0;
		}
	}
	error("bad expression");
}