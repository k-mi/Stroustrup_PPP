#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

// Tをバイトシーケンスとして扱う	
template<class T> char* as_byte(T& i){
	void* addr = &i;	// オブジェクトを格納するために使用されているメモリの
						// 1バイト目のアドレスを取得する
	return static_cast<char*>(addr);
}

int main(){
	// istreamをファイルからバイナリ入力モードで開く
	cout << "Please enter input file name\n";
	string name;
	cin >> name;
	ifstream ifs(name.c_str(), ios_base::binary);	// ストリームモード
	// "binary"を指定するとストリームがバイトをいじらなくなる
	if(!ifs) throw runtime_error("can't open input file " + name);

	// ostreamをファイルへのバイナリ出力モードで開く
	cout << "Please enter output file name\n";
	cin >> name;
	ofstream ofs(name.c_str(), ios_base::binary);	// ストリームモード
	// "binary"を指定するとストリームがバイトをいじらなくなる
	if(!ofs) throw runtime_error("can't open output file " + name);

	vector<int> v;

	// バイナリファイルからの読み取り
	int i;
	while(ifs.read(as_byte(i), sizeof(int)))	// バイトの読み取り
		v.push_back(i);

	// ... vを使ったなんらかの処理 ...

	// バイナリファイルへの書き込み
	for(int i = 0; i < v.size(); ++i)			// バイトの書き込み
		ofs.write(as_byte(v[i]), sizeof(int));
	
	return 0;
}