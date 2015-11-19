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

	Calculation:
		Statement
		Print
		Quit
		Calculation Statement

	Statement:
		Declaration
		Expression

	Print:
		";"

	Quit:
		"q"

	Declaration:
		"let" Name "=" Expression

	Name:
		英字で始まり、以降は英数字かアンダースコアの組み合わせになっている文字列

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term
	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
	Primary:
		Number
		"(" Expression ")"
		"-" Primary
		"+" Primary
	Number:
		floating-point-literal

	Input comes from cin through the Token_stream called us.	
*/

#include "std_lib_facilities.h"

const char number = '8';		// 数字の値を表す
const char quit = 'q';			// t.kind==quitはtが終了のトークンであることを意味する
const char print = ';';			// t.kind==printはtが出力のトークンであることを意味する

const char name = 'a';			// 名前トークン
const char let = 'L';			// 宣言トークン
const string declkey = "let";	// 宣言キーワード

const string prompt = "> ";
const string result = "= ";		// これに結果が続くことを表す

class Token{
public:
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n): kind(ch), name(n) {}
};

class Token_stream{
public:
	Token_stream();			// cinを読み取るToken_streamを作成する
	Token get();			// Tokenを取得する（get()は6.8.2で定義されている）
	void putback(Token t);	// Tokenを戻す
	void ignore(char c);	// cまでの（cを含む）文字を破棄する
private:
	bool full;				// バッファにTokenは含まれているか
	Token buffer;			// putback関数を使って戻すTokenをここで保管する
};

class Variable{
public:
	Variable(string n, double v) : name(n), value(v) { }

	string name;
	double value;
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
	    case '=':
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
	    	if(isalpha(ch)){
	    		string s;
	    		s += ch;
	    		while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
	    		cin.putback(ch);
	    		if(s == declkey) return Token(let);	// 宣言キーワード
	    		return Token(name, s);
	    	}
	        error("Bad token");
	}	
}

// cはTokenの種類を表す
void Token_stream::ignore(char c){
	// まずバッファを調べる
	if(full && c == buffer.kind){
		full = false;
		return;
	}
	full = false;

	// 次に入力を検索する
	char ch = 0;
	while(cin >> ch)
		if(ch == c) return;
}


vector<Variable> var_table;
Token_stream ts;			// get関数とputback関数を提供する

// sという名前のVariableの値を返す
double get_value(string s){
	for(int i = 0; i < var_table.size(); ++i)
		if(var_table[i].name == s) return var_table[i].value;
	error("get: undefined variable ", s);
}

/*
// sという名前のVariableをdに設定する
void set_value(string s, double d){
	for(int i = 0; i < var_table.size(); ++i){
		if(var_table[i].name == s){
			var_table[i].value = d;
			return;
		}
	}
	error("set: undefined variable ", s);
}
*/

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
		case number:					// 数字を表す
			return t.value;				// 数字の値を返す
		case name:
			return get_value(t.name);	// 変数の値を返す
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

// varはすでにvar_tableに含まれているか
bool is_declared(string var){
	for(int i = 0; i < var_table.size(); ++i)
		if(var_table[i].name == var) return true;
	return false;
}

// (var, val)をvar_tableに追加する
double define_name(string var, double val){
	if(is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable(var, val));
}

// "let"が検出されている前提とする
// name = expression を処理する
// "name"という名前の変数を初期値"expression"で宣言する
double declaration(){
	Token t = ts.get();
	if(t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if(t2.kind != '=') error("= missing in declaration of", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

void clean_up_mess(){
	ts.ignore(print);
}

double statement(){
	Token t = ts.get();
	switch(t.kind){
		case let:
			return declaration();
		default:
			ts.putback(t);
			return expression();
	}
}

void calculate(){
	while (cin){
		try{
	    	cout << prompt; 						// プロンプトを表示する
	    	Token t = ts.get();
	    	while(t.kind == print) t = ts.get();	// まず、すべてのprintを破棄する
	    	if(t.kind == quit) return;
			ts.putback(t);
	    	cout << result << statement() << endl;			
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