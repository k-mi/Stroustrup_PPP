class Token{
	char kind;
	double value;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
};

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