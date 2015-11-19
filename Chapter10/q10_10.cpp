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

	The grammer for input cin:

	Calculation:
		Statement
		Print
		Help
		Quit
		Calculation Statement
		"from" Name　（ファイル入力）	// 参考: http://handasse.blogspot.com/2009/05/c.html
		"to" Name　（ファイル出力）

	Statement:
		Declaration
		Expression

	Print:
		";"
		"\n"

	Quit:
		"quit"
	
	Help:
		"help"

	Declaration:
		"let" Name "=" Expression　（変数の宣言）
		"const" Name "=" Expression　（定数の宣言）

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term

	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
		Term "%" Primary
		Term "^" Primary

	Primary:
		Number
		Name
		Name "=" Expressoion　（変数への代入）
		"(" Expression ")"
		"-" Primary
		"+" Primary

	Number:
		floating-point-literal（浮動小数点数）

	Name:
		英字で始まり、以降は英数字かアンダースコアの組み合わせになっている文字列

	Assignment:		
		Name "=" Expression

	Input comes from cin through the Token_stream called us.	
*/

#include "std_lib_facilities.h"
#include <limits>

const char print = ';';			// 出力トークン
const char quit = 'q';			// 終了トークン
const char help = 'H';			// ヘルプトークン
const char number = '8';		// 数字トークン
const char name = 'a';			// 名前トークン
const char let = 'L';			// 宣言トークン
const char constt = 'C';		// 定数トークン
const char input = 'I';			// 入力トークン
const char output = 'O';		// 出力トークン

const string declkey = "let";	// 宣言キーワード
const string decckey = "const";	// 定数キーワード
const string quitkey = "quit";	// 終了キーワード
const string helpkey = "help";	// ヘルプキーワード
const string inputkey = "from";	// 入力キーワード
const string outputkey = "to";	// 出力キーワード

const string prompt = "> ";		// プロンプトの表示テキスト
const string result = "= ";		// これに結果が続く

streambuf* coutbuf = cout.rdbuf();
streambuf* cinbuf = cin.rdbuf();

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
	Variable(string n, double v, bool c) : name(n), value(v), const_val(c){ }

	string name;
	double value;
	bool const_val;			// 定数: true, 変数: false
};

class Table{
public:
	double get(string s);
	void set(string s, double d);
	double define(string var, double val, bool c);

private:
	vector<Variable> var_table;
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

	char ch = cin.get();		// 1文字取得（ホワイトスペースを読み飛ばさない）
	while(isspace(ch)){
		if(ch == '\n') break;	// 改行のみ特別にswitch文で扱う
		ch = cin.get();
	}

	switch(ch){
		case print:	// 出力
	    case '(': 
	    case ')': 
	    case '+':
	    case '-':
	    case '*':
	    case '/':
	    case '%':
	    case '^':
	    case '=':
	        return Token(ch);	// 文字をそのまま出力する
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':	// 数値リテラル
	        {    
	            cin.putback(ch);         	// 数字を入力ストリームに戻す
	            double val;
	            cin >> val;              	// 整数を読み取る
	            return Token(number, val);
	        }
	    case '\n':
	    	return Token(print);			// 改行を出力として扱う
	    default:
	    	if(isalpha(ch)){
	    		string s;
	    		s += ch;
	    		while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '.')) s += ch;
	    		cin.putback(ch);
	    		if(s == declkey) return Token(let);		// 宣言キーワード
	    		if(s == decckey) return Token(constt);	// 定数キーワード
	    		if(s == quitkey) return Token(quit);	// 終了キーワード
	    		if(s == helpkey) return Token(help);	// ヘルプキーワード
	    		if(s == inputkey) return Token(input);	// 入力キーワード
	    		if(s == outputkey) return Token(output);// 出力キーワード
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

// sという名前のVariableの値を返す
double Table::get(string s){
	for(int i = 0; i < var_table.size(); ++i)
		if(var_table[i].name == s) return var_table[i].value;
	error("get: undefined variable ", s);
}

// sという名前のVariableをdに設定する
void Table::set(string s, double d){
	for(int i = 0; i < var_table.size(); ++i){
		if(var_table[i].name == s){
			if(var_table[i].const_val == true) error("set: const variable ", s);
			var_table[i].value = d;
			return;
		}
	}
	error("set: undefined variable ", s);
}

// (var, val, c)をvar_tableに追加する
double Table::define(string var, double val, bool c){
	for(int i = 0; i < var_table.size(); ++i)
		if(var_table[i].name == var)
			error(var, " declared twice");	// すでにvar_tableに含まれている
	var_table.push_back(Variable(var, val, c));
}

Token_stream ts;	// get関数とputback関数を提供する
Table symbol_table;	// Tableへの操作を提供する

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
			{
				Token t2 = ts.get();
				if(t2.kind == '='){				// 変数に値を代入
					double d = expression();
					symbol_table.set(t.name, d);
					return d;
				}			
				else{
					ts.putback(t2);
					return symbol_table.get(t.name);	// 変数の値を返す
				}
			}
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
			case '^':
				{
					double d = primary();
					int i2 = int(d);
					if(i2 != d) error("right-hand operand of % not int");
					if(i2 < 0) error("right-hand operand is negative");
					left = pow(left, i2);
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
	double left = term();	// Termを読み取って評価する
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

// "let"が検出されている前提とする
// name = expression を処理する
// "name"という名前の変数を初期値"expression"で宣言する
double declaration(){
	Token t = ts.get();
	bool constflag = t.kind == constt ? true : false;

	t = ts.get();
	if(t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if(t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	symbol_table.define(var_name, d, constflag);
	return d;
}

void clean_up_mess(){
	ts.ignore(print);
}

double statement(){
	Token t = ts.get();
	switch(t.kind){
		case let:
		case constt:
			ts.putback(t);
			return declaration();	// 変数・定数の宣言
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
	    	while(t.kind == print) t = ts.get();	// すべてのprintを破棄する
			
	    	switch(t.kind){
	    		case help:		// ヘルプを表示する
					cout << "Simple calculator help text" << endl;
					continue;
				case quit:		// 計算を終了する
					if(t.kind == quit)
					return;
				case input:		// ファイル入力
				{
					t = ts.get();
					if(t.kind != name) error("name expected in input");
					static ifstream ifs(t.name);
					if(!ifs){ 
						cin.rdbuf(cinbuf);
						error("can't open input file: ", t.name);
					}
					cin.rdbuf(ifs.rdbuf());
					break;					
				}
				case output:	// ファイル出力
				{
					t = ts.get();
					if(t.kind != name) error("name expected in output");
					static ofstream ofs(t.name);
					if(!ofs){
    					cout.rdbuf(coutbuf);
						error("can't open output file: ", t.name);
					}
					cout.rdbuf(ofs.rdbuf());
					break;					
				}
				default:
					ts.putback(t);
    				cout << result << statement() << endl;
    				break;				
	    	}
		}
		catch(exception& e){
			cout << e.what() << endl;
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
	    cout << e.what() << endl;
	    keep_window_open("~~");
	    return 1;
	}
	catch (...) {
	    cout << "exception \n";
	    keep_window_open("~~");
	    return 2;
	}	
}