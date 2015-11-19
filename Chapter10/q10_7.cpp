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
		Help
		Quit
		Calculation Statement

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
		アラビア数字[1:3999]

	Name:
		英字で始まり、以降は英数字かアンダースコアの組み合わせになっている文字列

	Assignment:		
		Name "=" Expression

	Input comes from cin through the Token_stream called us.	
*/

#include "std_lib_facilities.h"
#include <map>
#include <limits>

const char print = ';';			// 出力トークン
const char quit = 'q';			// 終了トークン
const char help = 'H';			// ヘルプトークン
const char number = '8';		// 数字トークン
const char name = 'a';			// 名前トークン
const char let = 'L';			// 宣言トークン
const char constt = 'C';		// 定数トークン

const string declkey = "let";	// 宣言キーワード
const string decckey = "const";	// 定数キーワード
const string quitkey = "quit";	// 終了キーワード
const string helpkey = "help";	// ヘルプキーワード

const string prompt = "> ";		// プロンプトの表示テキスト
const string result = "= ";		// これに結果が続く

map<int, char> romanintlist;	// key: アラビア数字、value: ローマ数字
map<int, string> intromanlist;	// key: アラビア数字、value: ローマ数字

// ローマ数字の置換リスト
void init_romanintlist(map<int, char>& m){
	m.insert(make_pair(1, 'I'));
	m.insert(make_pair(5, 'V'));
	m.insert(make_pair(10, 'X'));
	m.insert(make_pair(50, 'L'));
	m.insert(make_pair(100, 'C'));
	m.insert(make_pair(500, 'D'));
	m.insert(make_pair(1000, 'M'));
}

void init_intromanlist(map<int, string>& m){
	m.insert(make_pair(1, "I"));
	m.insert(make_pair(4, "IV"));
	m.insert(make_pair(5, "V"));
	m.insert(make_pair(9, "IX"));
	m.insert(make_pair(10, "X"));
	m.insert(make_pair(40, "XL"));
	m.insert(make_pair(50, "L"));
	m.insert(make_pair(90, "XC"));
	m.insert(make_pair(100, "C"));
	m.insert(make_pair(400, "CD"));
	m.insert(make_pair(500, "D"));
	m.insert(make_pair(900, "CM"));
	m.insert(make_pair(1000, "M"));
}

class Roman_int{
public:
	Roman_int() : m_num(0) { }
	Roman_int(int i) : m_num(i) { }
	Roman_int(string s);

	int as_int() const { return m_num; } 	// int型の値を返す
private:
	int m_num;
};

// ローマ数字をint型に変換してm_numに格納
Roman_int::Roman_int(string s){
	int sum = 0, tmp = 0;
	map<int, char>::iterator it;

	for(int i = 0; i < s.size(); ++i){
		for(map<int, char>::iterator it = romanintlist.begin(); it != romanintlist.end(); ++it){
			if(s[i] == it->second){
				if(tmp < it->first && i != 0){	// IV(9)など減算のパターンの場合
					sum += it->first - tmp - tmp;
					tmp = numeric_limits<int>::max();
				}
				else{							// 通常の場合
					sum += it->first;	
					tmp = it->first;			
				}
				break;
			}
		}
	}
	m_num = sum;
}

istream& operator>>(istream& is, Roman_int& r){
	string tmp;
	is >> tmp;
	if(!is) return is;
	r = Roman_int(tmp);
	return is;
}

ostream& operator<<(ostream& os, Roman_int& r){
	int tmp = r.as_int();
	while(tmp > 0){
		for(map<int, string>::reverse_iterator it = intromanlist.rbegin(); it != intromanlist.rend(); ++it){
			if(tmp - it->first >= 0){	
				os << it->second;
				tmp -= it->first;
				break;
			}
		}
	}
	return os;
}

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
	    case 'I': 
	    case 'V': 
	    case 'X': 
	    case 'L': 
	    case 'C':
	    case 'D': 
	    case 'M':							// ローマ数字で扱う文字
	        {    
	            cin.putback(ch);         	// 入力ストリームに戻す
	            Roman_int val;
	            cin >> val;              	// ローマ数字を読み取る
	            return Token(number, val.as_int());
	        }
	    case '\n':
	    	return Token(print);			// 改行を出力として扱う
	    default:
	    	if(isalpha(ch)){
	    		string s;
	    		s += ch;
	    		while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
	    		cin.putback(ch);
	    		if(s == declkey) return Token(let);		// 宣言キーワード
	    		if(s == decckey) return Token(constt);	// 定数キーワード
	    		if(s == quitkey) return Token(quit);	// 終了キーワード
	    		if(s == helpkey) return Token(help);	// ヘルプキーワード
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
			
	    	if(t.kind == help){		// ヘルプを表示する
				cout << "Simple calculator help text" << endl;
				continue;
	    	}	

	    	if(t.kind == quit) return;
			ts.putback(t);

			// ローマ数字の範囲に収まるかチェック
			double d = statement();
			if(d > 3999) error("overflow");
			if(d < 1) error("underflow");
			Roman_int r((int)d);
	    	cout << result << r << endl;	// ローマ数字として出力		    		
		}
		catch(exception& e){
			cerr << e.what() << endl;
			clean_up_mess();
		}
    }
}

// メインループとエラーの処理
int main(){
	init_romanintlist(romanintlist);
	init_intromanlist(intromanlist);

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