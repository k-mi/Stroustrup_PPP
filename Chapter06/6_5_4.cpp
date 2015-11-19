class Token{
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

double expression(){
	double left = term();		// Termを読み取って評価する
	Token t = get_token();		// 次のトークンを取得する

	while(t.kind == '+' || t.kind == '-'){	// +または-を探す
		if(t.kind == '+')
			left += term();		// Termを評価して足す
		else
			left -= term();		// Termを評価して引く
		t = get_token();
	}

	return left;	// +または-はもう残っていないので、答えを返す
}