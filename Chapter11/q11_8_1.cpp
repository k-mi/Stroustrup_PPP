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
	ofstream ofs(name.c_str());
	if(!ofs) throw runtime_error("can't open output file " + name);

	vector<short> v;

	// バイナリファイルからの読み取り
	char c;
	while(ifs.read(as_byte(c), sizeof(char)))	// バイトの読み取り
		v.push_back(c);

	// 書き込み
	for(int i = 0; i < v.size(); ++i)			// 数値を書き込み
		ofs << (int)v[i] << endl;
	
	return 0;
}