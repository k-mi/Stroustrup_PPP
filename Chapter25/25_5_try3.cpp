// TEA(Tiny Encryption Algorithm) encipher
// LP64環境だと(unsigned)longが64bit整数になってしまうため、(u)int32_tに変更

#include <cstdint>		// uint32_t (C++11 optional)
#include <iostream>
#include <fstream>
#include <iomanip>		// setw, setfill
#include <stdexcept>	// runtime_error
using namespace std;

void encipher(const uint32_t* const v,	// 暗号化する8文字（2つuint32_t配列）
			  uint32_t* const w,		// 出力先（2つのuint32_t配列）
			  const uint32_t* const k){	// 鍵を表す（4つのuint32_t配列）
	uint32_t y = v[0];
	uint32_t z = v[1];
	uint32_t sum = 0;
	uint32_t delta = 0x9E3779B9;
	uint32_t n = 32;

	while(n-- > 0){
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];	
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

	uint32_t outptr[2];
	char inbuf[nchar];
	uint32_t* inptr = reinterpret_cast<uint32_t*>(inbuf);
	int count = 0;

	while(inf.get(inbuf[count])){
		outf << hex;	// 16進出力を使用する
		if(++count == nchar){
			encipher(inptr, outptr, k);
			// 前0でパディング
			outf << setw(8) << setfill('0') << outptr[0] << ' '
				 << setw(8) << setfill('0') << outptr[1] << ' ';
			count = 0;
		}
	}

	if(count){	// パディング
		//while(count != nchar) inbuf[count++] = '0';
		while(count != nchar) inbuf[count++] = '\0';	// 変更: ヌル文字を詰める
		encipher(inptr, outptr, k);
		outf << outptr[0] << ' ' << outptr[1] << ' ';
	}
}