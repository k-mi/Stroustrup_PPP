// TEA(Tiny Encryption Algorithm) decipher
// LP64環境だと(unsigned)longが64bit整数になってしまうため、(u)int32_tに変更

#include <cstdint>		// uint32_t (C++11 optional)
#include <iostream>
#include <fstream>
#include <iomanip>		// setw, setfill
#include <stdexcept>	// runtime_error
using namespace std;

void decipher(const uint32_t* const v,	// 複合化する8文字（2つuint32_t配列）
			  uint32_t* const w,		// 出力先（2つのuint32_t配列）
			  const uint32_t* const k){	// 鍵を表す（4つのuint32_t配列）
	uint32_t y = v[0];
	uint32_t z = v[1];
	uint32_t sum = 0xC6EF3720;
	uint32_t delta = 0x9E3779B9;
	uint32_t n = 32;
	// sum = delta << 5, in general sum = delta * n
	while(n-- > 0){
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}
	w[0] = y;
	w[1] = z;
}

int main(){	// 送り手
	const int nchar = 2 * sizeof(int32_t);	// 64ビット
	const int kchar = 2 * nchar;			// 128ビット

	//string op;
	string key;
	string infile;
	string outfile;
	cout << "please enter input file name, output file name, and key:\n";
	cin >> infile >> outfile >> key;
	while(key.size() < kchar) key += '0';	// パディングキー
	ifstream inf(infile.c_str());
	ofstream outf(outfile.c_str());
	if(!inf || !outf) throw runtime_error("bad file name");

	const uint32_t* k = reinterpret_cast<const uint32_t*>(key.data());

	uint32_t inptr[2];
	char outbuf[nchar+1];
	outbuf[nchar] = 0;	// ターミネータ
	uint32_t* outptr = reinterpret_cast<uint32_t*>(outbuf);
	inf.setf(ios_base::hex, ios_base::basefield);	// 16進入力を使用する

	while(inf >> inptr[0] >> inptr[1]){
		decipher(inptr, outptr, k);
		outf << outbuf;
	}
}