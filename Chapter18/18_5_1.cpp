const int max = 100;
int gai[max];			// （100個のintからなる）グローバル配列: 永遠の存在

void f(int n){
	char lac[20];		// ローカル配列: スコープの終わりまで存続する
	int lai[60];
	//double lad[n];	// エラー: 配列のサイズが定数ではない

	// ...
}

void f2(){
	char lac[20];		// ローカル配列: スコープの終わりまで存続する

	lac[7] = 'a';
	*lac = 'b';			// lac[0] = 'b'に相当する

	lac[-2] = 'b';		// エラー（コンパイルはされるがwarning）
	lac[200] = 'c';		// エラー（コンパイルはされるがwarning）
}

int main(){
	f(10);
	f2();
}