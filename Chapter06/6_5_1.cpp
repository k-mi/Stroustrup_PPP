class Token{
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

double expression(){
	double left = expression();		// Expressionを読み取って評価する
	Token t = get_token();			// 次のトークンを取得する

	switch(t.kind){					// トークンの種類を調べる
		case '+':				
			return left + term();	// Termを読み取って評価し、加算を実行する
		case '-':
			return left - term();	// Termを読み取って評価し、減算を実行する
		default:
			return left;			// Expressionの値を返す
	}
}