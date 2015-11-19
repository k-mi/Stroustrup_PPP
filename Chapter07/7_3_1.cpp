#include "std_lib_facilities.h"

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
	if(full){		// Tokenがすでに含まれているか
		// Tokenをバッファから削除する
		full = false;
		return buffer;		
	}

	char ch;
	cin >> ch;		// >>はホワイトスペースを読み飛ばす

	switch(ch){
		case ';':	// 出力
		case 'q':	// 終了
	    case '(': case ')': case '+': case '-': case '*': case '/': 
	        return Token(ch);	// 文字をそのまま出力する
	    case '.':
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':
	        {    
	            cin.putback(ch);         // 数字を入力ストリームに戻す
	            double val;
	            cin >> val;              // 浮動小数点数を読み取る
	            return Token('8',val);   // '8'は「数字」を表す
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
		case '8':				// '8'を使って数字を表す
			return t.value;		// 数字の値を返す
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

// メインループとエラーの処理
int main(){
	try {
		double val = 0;
	    while (cin){
	    	cout << "> "; 						// プロンプトを表示する
	    	Token t = ts.get();
	    	if(t.kind == 'q') break;			// 'q'は「終了」を表す
	    	if(t.kind == ';')					// ';'は「今すぐ出力」を表す
	    		cout << "= " << val << '\n';	// 結果を表示する
	    	else
	    		ts.putback(t);
	    	val = expression();
	    }
	    keep_window_open("~0");
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		keep_window_open("~~");
		/*
		cout << "Please enter the character ~ to close the window\n";
		char ch;
		while(cin >> ch)	// ~が検出されるまで読み取りを続ける
			if(ch == '~') return 1;
		*/
		return 1;
	}
	catch (exception& e) {
	    cerr << e.what() << endl;
	    keep_window_open("~1");
	    return 1;
	}
	catch (...) {
	    cerr << "exception \n";
	    keep_window_open("~2");
	    return 2;
	}	
}