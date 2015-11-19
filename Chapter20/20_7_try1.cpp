#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 一致するか
template<class T> bool is_equal(T first, T second, T d_first){
	for(T it = first; it != second; ++it){
		if(*it != *d_first) return false;
		++d_first;
	}
	return true;
}

// 先のオブジェクト（第1、2引数に指定）のほうが辞書式で先になるか
template<class T> bool is_previous(T first, T second, T d_first){
	for(T it = first; it != second; ++it){
		if(*it < *d_first) return true;
		++d_first;
	}
	return false;
}

void test(char* c){
	char hello[] = "Hello";
	char howdy[] = "Howdy";

	int size;	// cのサイズ
	for(size = 0; c[size] != '\0'; ++size);

	if(is_equal(c, c + size, hello)) cout << "equal" << endl;
	else cout << "not equal" << endl;
	if(is_previous(c, c + size, howdy)) cout << "previous" << endl;
	else cout << "not previous" << endl;
}

void test(vector<char>& v){
	vector<char> hello = { 'H', 'e', 'l', 'l', 'o' };
	vector<char> howdy = { 'H', 'o', 'w', 'd', 'y' };

	if(v == hello) cout << "equal" << endl;		// is_equal(v.begin(), v.end(), hello.begin())
	else cout << "not equal" << endl;
	if(v < howdy) cout << "previous" << endl;	// is_previous(v.begin(), v.end(), howdy.begin())
	else cout << "not previous" << endl;
}

void test(list<char>& l){
	list<char> hello = { 'H', 'e', 'l', 'l', 'o' };
	list<char> howdy = { 'H', 'o', 'w', 'd', 'y' };

	if(l == hello) cout << "equal" << endl;		// is_equal(l.begin(), l.end(), hello.begin())
	else cout << "not equal" << endl;
	if(l < howdy) cout << "previous" << endl;	// is_previous(l.begin(), l.end(), howdy.begin())
	else cout << "not previous" << endl;
}

void test(string& s){
	string hello = "Hello";
	string howdy = "Howdy";

	if(s == hello) cout << "equal" << endl;		// is_equal(&s[0], &s[s.size()], &hello[0])
	else cout << "not equal" << endl;			// is_equal(s.begin(), s.end(), hello.begin())
	if(s < howdy) cout << "previous" << endl;	// is_previous(&s[0], &s[s.size()], &howdy[0])
	else cout << "not previous" << endl;		// is_equal(s.begin(), s.end(), howdy.begin())
}

int main(){
	char c[] = "Hello";
	vector<char> vc = { 'H', 'e', 'l', 'l', 'o' };	// -std=c++11オプション
	list<char> lc = { 'H', 'e', 'l', 'l', 'o' };	// -std=c++11オプション
	string s = "Hello";

	test(c);
	test(vc);
	test(lc);
	test(s);

	// コピー
	int size = sizeof(c) / sizeof(c[0]);
	char* c2 = new char[size];
	for(int i = 0; i < size; ++i)
		c2[i] = c[i];
	test(c2);
	delete[] c2;

	vector<char> vc2 = vc;
	list<char> lc2 = lc;
	string s2 = s;
	test(vc2);
	test(lc2);
	test(s2);
}