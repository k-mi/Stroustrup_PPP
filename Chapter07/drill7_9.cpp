/*
	Simple calculator(drill7)

	The grammer for input is:

	Calculate:
		Input
		Statement
		Print
		Quit

	Quit:
		"q"

	Print:
		";"

	Statement:
		Declaraion
		Expression

	Declaration:
		"let" Name "=" Expression

	Function:
		"sqrt" "(" Expression ")"
		"pow" "(" Expression "," Expression ")"

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term

	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
		Term "%" Primary

	Primary:
		Number
		"(" Expression ")"
		"-" Primary
		Name
		Function

	Number:
		floating-point-number

	Name:
		alphabet alphabet/digit ...

*/

#include "std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) { }
	Token(char ch, double val) : kind(ch), value(val) { }
	Token(char ch, string s) : kind(ch), name(s) { }
};

class Token_stream {
	bool full;		// bufferに値が入っているかどうか
	Token buffer;	// バッファー
public:
	Token_stream() :full(false), buffer(0) { }

	Token get();
	void unget(Token t) { buffer=t; full=true; }	// トークンを戻す

	void ignore(char);
};

const char let = 'L';		// 宣言トークン
const char quit = 'Q';		// 終了トークン
const char print = ';';		// 出力トークン
const char number = '8';	// 数字トークン
const char name = 'a';		// 名前トークン
const char funct = 'f';		// 関数トークン

Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':	// 関数で使用する記号
	case print:	// 出力トークン
		return Token(ch);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		{	
			cin.unget();	// 最後に読み取った文字を戻す
			double val;
			cin >> val;
			return Token(number, val);	// 数字トークンと数値
		}
	case '.':	// 浮動小数点数は'.'から始まる場合もある
		{
			while(cin.get(ch) && ch == '.') { }	// 前方の'.'の重複を飲み込む		
			cin.unget();	// 最後に読み取った文字を戻す
			cin.putback('.');
			double val;
			cin >> val;
			if(!cin)		// 後方の'.'の重複を飲み込む
				cin.clear();			
			return Token(number, val);	// 数字トークンと数値
		}	
	default:
		if (isalpha(ch)) {	// 最初が英字であるか確認
			string s;
			s += ch;
			// 以降の文字を1文字ずつ英数字であるか確認して読み込み
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "let") return Token(let);			// 宣言トークン
			if (s == "q") return Token(quit);			// 終了トークン
			if (s == "sqrt" || s == "pow") 
				return Token(funct, s);	// 関数トークンと関数名
			return Token(name, s);						// 名前トークンと変数名
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
public:
	Variable(string n, double v) : name(n), value(v) { }
	string name;	// 変数名
	double value;	// 値
};

vector<Variable> names;	

// sという変数名の値を返す
double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

/*
void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}
*/

// namesベクタにnameが含まれているか
bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();	// primary関数内で呼び出すためのプロトタイプ宣言

double func()
{
	Token t = ts.get();
	if (ts.get().kind == '(') {
		if(t.name == "sqrt"){
			double d = expression();
			t = ts.get();
			if (t.kind != ')') error("')' expected");
			if (d < 0) error("sqrt() parameter is negative number ");
			return sqrt(d);			// 平方根を返す
		}
		else if(t.name == "pow"){
			double d1 = expression();
			t = ts.get();
			if (t.kind != ',') error("',' expected");
			double d2 = expression();
			int i2 = int(d2);
			if (i2 < 0) error("second parameter is negative number ");
			if (i2 != d2) error("second parameter is not integer");
			t = ts.get();
			if (t.kind != ')') error("')' expected");
			return pow(d1, i2);		// べき乗を返す
		}
	}
	else
		error("'(' expected");
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
		case '(':
		{	double d = expression();
			t = ts.get();
			if (t.kind != ')') error("')' expected");
			return d;
		}
		case '-':
			return - primary();
		case number:
			return t.value;				// 数字トークンの場合は値を返す
		case name:
			return get_value(t.name);	// 名前トークンの場合は変数の値を返す
		case funct:
			ts.unget(t);
			return func();				// 関数の結果を返す
		default:
			error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
			case '*':
				left *= primary();
				break;
			case '/':
				{	double d = primary();
					if (d == 0) error("divide by zero");	// ゼロ除算
					left /= d;
					break;
				}
			case '%':
				{	
					double d = primary();
					int v1 = int(left);
					if (v1 != left) error("left-hand operand is not integer");
					int v2 = int(d);
					if (v2 != d) error("right-hand operand is not integer");
					if (v2 == 0) error("mod: divide by zero");	// ゼロ除算
					left = v1 % v2;
					break;
				}
			default:
				ts.unget(t);
				return left;
			}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
			case '+':
				left += term();
				break;
			case '-':
				left -= term();
				break;
			default:
				ts.unget(t);
				return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");	// 名前トークンでない場合
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");	// すでに同じ名前の変数が定義されている場合
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);	// 文法の"="がない場合
	double d = expression();
	names.push_back(Variable(t.name, d));	// namesに変数名と値を追加
	return d;
}

// トークンが"let"であればDecleartion
// それ以外であればExpressionとして処理
double statement()
{
	Token t = ts.get();
	switch(t.kind) {
		case let:
			return declaration();
		default:
			ts.unget(t);
			return expression();
	}
}

// Token_streamを出力トークンまで読み飛ばす
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";		// プロンプトとして表示される文字列
const string result = "= ";		// 結果の出力時に表示される文字列

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();	// 出力トーンを飲み込む
		if (t.kind == quit) return;			// 終了トークンの場合は終了する
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
	try {
		names.push_back(Variable("k", 1000));	// 変数の定義

		calculate();		// 計算
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >> c && c != ';');	// ';'が入力されたら終了
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin >> c && c != ';');	// ';'が入力されたら終了
		return 2;
	}