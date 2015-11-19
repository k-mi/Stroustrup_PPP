#include "std_lib_facilities.h"

class Token{
public:
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

Token get_token()    // read a token from cin
{
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
 //not yet   case ';':    // for "print"
 //not yet   case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/': 
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

double expression();
double term();

double primary(){
	Token t = get_token();
	switch(t.kind){
		case '(':				// '(' Expression ')'を処理する
			{
				double d = expression();
				t = get_token();
				if(t.kind != ')') error("')' expected");
				return d;			
			}
		case '8':				// '8'を使って数字を表す
			return t.value;		// 数字の値を返す
		default:
			error("primary expected");
	}
}

int main(){
	try {
	    while (cin){
	    	double tmp = expression();
	        cout << "= " << tmp << '\n';	// バージョン1
	    }
	    keep_window_open("~0");
	}
	catch (exception& e) {
	    cerr << e.what() << endl;
	    keep_window_open ("~1");
	    return 1;
	}
	catch (...) {
	    cerr << "exception \n";
	    keep_window_open ("~2");
	    return 2;
	}	
}

double expression(){
	double left = term();		// Termを読み取って評価する
	Token t = get_token();		// 次のトークンを取得する

	while(true){	// +または-を探す
		switch(t.kind){
			case '+':
				left += term();		// Termを評価して足す
				t = get_token();
				break;
			case '-':
				left -= term();		// Termを評価して引く
				t = get_token();
				break;
			default:
				return left;		// +または-はもう残っていないので、答えを返す			
		}
	}
}

double term(){
	double left = primary();
	Token t = get_token();
	while(true){
		switch(t.kind){
			case '*':
				left *= primary();
				t = get_token();
				break;
			case '/':
				{
					double d = primary();
					if(d == 0) error("divide by zero");
					left /= d;
					t = get_token();
					break;
				}
			default:
				return left;
		}
	}
}