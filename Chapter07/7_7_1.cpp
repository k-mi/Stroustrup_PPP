/*
	Simple calculator

	Revision history:

		Revised by Bjarne Stroustrup May 2007
		Revised by Bjarne Stroustrup August 2006
		Revised by Bjarne Stroustrup August 2004
		Originally written by Bjarne Stroustrup
			(bs@cs.tamu.edu) Spring 2004.

	This program implements a basic expression callulator.
	Input from cin; output to cout.

	The grammer for input is:

	Statement:
		Expression
		Print
		Quit

	Print:
		;

	Quit:
		q

	Expression:
		Term
		Expression + Term
		Expression - Term
	Term:
		Primary
		Term * Primary
		Term / Primary
	Primary:
		Number
		( Expression )
		- Primary
		+ Primary
	Number:
		floating-point-literal

	Input comes from cin through the Token_stream called us.	
*/

#include "std_lib_facilities.h"

const char number = '8';	// 数字の値を表す
const char quit = 'q';		// t.kind==quitはtが終了のトークンであることを意味する
const char print = ';';		// t.kind==printはtが出力のトークンであることを意味する
const string prompt = "> ";
const string result = "= ";	// これに結果が続くことを表す

class Token{
public:
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

class Token_stream{
public:
	Token_stream();			// cinを読み取るToken_streamを作成する
	Token get();			// Tokenを取得する（get()は6.8.2で定義されている）
	void putback(Token t);	// Tokenを戻す
private:
	bool full;				// バッファにTokenは含まれているか
	Token buffer;			// putback関数を使って戻すTokenをここで保管する
};

Token_stream::Token_stream() : full(false), buffer(0){}
void Token_stream::putback(Token t){
	if(full) error("putback() into a full buffer");
	buffer = t;		// tをバッファにコピーする
	full = true;	// bufferは現在fullである
}
Token Token_stream::get(){
	if(full){		// Tokenがすでに読み込まれているか
		// Tokenをバッファから削除する
		full = false;
		return buffer;		
	}

	char ch;
	cin >> ch;		// >>はホワイトスペースを読み飛ばす

	switch(ch){
		case print:	// 出力
		case quit:	// 終了
	    case '(': 
	    case ')': 
	    case '+':
	    case '-':
	    case '*':
	    case '/':
	    case '%':
	        return Token(ch);	// 文字をそのまま出力する
	    case '.':				// 浮動小数点数はドットで始まることがある
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':	// 数値リテラル
	        {    
	            cin.putback(ch);         	// 数字を入力ストリームに戻す
	            double val;
	            cin >> val;              	// 浮動小数点数を読み取る
	            return Token(number, val);
	        }
	    default:
	        error("Bad token");
	}	
}

Token_stream ts;		// get関数とputback関数を提供する
double expression();	// primary関数からexpression関数を呼び出せるようにする宣言

double primary(){
	Token t = ts.get();
	switch(t.kind){
		case '(':				// '(' Expression ')'を処理する
			{
				double d = expression();
				t = ts.get();
				if(t.kind != ')') error("')' expected");
				return d;			
			}
		case number:			// 数字を表す
			return t.value;		// 数字の値を返す
		case '-':
			return -primary();
		case '+':
			return primary();
		default:
			error("primary expected");
	}
}

double term(){
	double left = primary();
	Token t = ts.get();
	while(true){
		switch(t.kind){
			case '*':
				left *= primary();
				t = ts.get();
				break;
			case '/':
				{
					double d = primary();
					if(d == 0) error("divide by zero");
					left /= d;
					t = ts.get();
					break;
				}
			case '%':
				{
					double d = primary();
					int i1 = int(left);
					if(i1 != left) error("left-hand operand of % not int");
					int i2 = int(d);
					if(i2 != d) error("right-hand operand of % not int");
					if(i2 == 0) error("%: divide by zero");
					left = i1 % i2;
					t = ts.get();
					break;
				}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double expression(){
	double left = term();		// Termを読み取って評価する
	Token t = ts.get();		// 次のトークンを取得する

	while(true){	// +または-を探す
		switch(t.kind){
			case '+':
				left += term();		// Termを評価して足す
				t = ts.get();
				break;
			case '-':
				left -= term();		// Termを評価して引く
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;		// +または-はもう残っていないので、答えを返す			
		}
	}
}

void clean_up_mess(){
	while(true){
		Token t = ts.get();		// printが見つかるまでスキップする
		if(t.kind == print) return;
	}
}

// 式評価ループ
void calculate(){
	while (cin){
		try{
	    	cout << prompt; 						// プロンプトを表示する
	    	Token t = ts.get();
	    	while(t.kind == print) t = ts.get();	// まず、すべてのprintを破棄する
	    	if(t.kind == quit) return;
			ts.putback(t);
	    	cout << result << expression() << endl;			
		}
		catch(exception& e){
			cerr << e.what() << endl;
			clean_up_mess();
		}
    }
}

// メインループとエラーの処理
int main(){
	try {
	    calculate();
	    keep_window_open();	// windowsのコンソールモードに対処する
	    return 0;
	}
	catch (runtime_error& e) {
	    cerr << e.what() << endl;
	    keep_window_open("~~");
	    return 1;
	}
	catch (...) {
	    cerr << "exception \n";
	    keep_window_open("~~");
	    return 2;
	}	
}