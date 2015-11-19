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
	cout << "Please enter input file name\n";
	string name;
	cin >> name;
	ifstream ifs(name.c_str());
	if(!ifs) throw runtime_error("can't open input file " + name);

	// ostreamをファイルへのバイナリ出力モードで開く
	cout << "Please enter output file name\n";
	cin >> name;
	ofstream ofs(name.c_str(), ios_base::binary);	// ストリームモード
	// "binary"を指定するとストリームがバイトをいじらなくなる
	if(!ofs) throw runtime_error("can't open output file " + name);

	vector<char> v;

	int i;
	while(ifs >> i)	// int型の数値を読み取り
		v.push_back((char)i);

	// バイナリファイルへの書き込み
	for(int i = 0; i < v.size(); ++i)	// バイトの書き込み
		ofs.write(as_byte(v[i]), sizeof(char));
	
	return 0;
}