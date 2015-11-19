#include <iostream>
#include <set>			// (C++11)
#include <algorithm>	// sort
#include <cstdlib>		// rand, srand
#include <ctime>		// time, clock
using namespace std;

int randint(int n){
	if(n <= 0) return 0;
	return rand() % n;
}

// [0:100)の範囲内の長さを持つランダムな文字列を生成
string strrand(){
	string s = "";
	while(randint(100)){
		int r = randint(62);
		if(r < 10) s += char(r + 48);		// 0-9
		else if(r < 36) s += char(r + 55);	// A-Z
		else s += char(r + 61);				// a-z
	}
	return s; 
}

int main(){
	srand(time(NULL));
	clock_t t1, t2;

	// 500,000
	set<string> s1;	// mapからsetに変更
	t1 = clock();
	if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");
	
	for(int i = 0; i < 500000; ++i)
		s1.insert(strrand());

	t2 = clock();
	if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
	cout << "500,000 string insert (use set): " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;

	// 5,000,000
	set<string> s2;
	t1 = clock();
	if(t1 == clock_t(-1)) throw runtime_error("sorry, no clock");

	for(int i = 0; i < 5000000; ++i) 
		s2.insert(strrand());

	t2 = clock();
	if(t2 == clock_t(-1)) throw runtime_error("sorry, clock overflow");
	cout << "5,000,000 string insert (use set): " << double(t2 - t1) / CLOCKS_PER_SEC << "[s]" << endl;
}