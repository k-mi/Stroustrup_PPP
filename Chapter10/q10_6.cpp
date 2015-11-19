#include <iostream>
#include <limits>
#include <map>
using namespace std;

map<int, char> romanintlist;	// key: アラビア数字、value: ローマ数字
map<int, string> intromanlist;	// key: アラビア数字、value: ローマ数字

// ローマ数字の置換リスト
void init_romanintlist(map<int, char>& m){
	m.insert(make_pair(1, 'I'));
	m.insert(make_pair(5, 'V'));
	m.insert(make_pair(10, 'X'));
	m.insert(make_pair(50, 'L'));
	m.insert(make_pair(100, 'C'));
	m.insert(make_pair(500, 'D'));
	m.insert(make_pair(1000, 'M'));
}

void init_intromanlist(map<int, string>& m){
	m.insert(make_pair(1, "I"));
	m.insert(make_pair(4, "IV"));
	m.insert(make_pair(5, "V"));
	m.insert(make_pair(9, "IX"));
	m.insert(make_pair(10, "X"));
	m.insert(make_pair(40, "XL"));
	m.insert(make_pair(50, "L"));
	m.insert(make_pair(90, "XC"));
	m.insert(make_pair(100, "C"));
	m.insert(make_pair(400, "CD"));
	m.insert(make_pair(500, "D"));
	m.insert(make_pair(900, "CM"));
	m.insert(make_pair(1000, "M"));
}

class Roman_int{
public:
	Roman_int() : m_num(0) { }
	Roman_int(int i) : m_num(i) { }
	Roman_int(string s);

	int as_int() const { return m_num; } 	// int型の値を返す
private:
	int m_num;
};

// ローマ数字をint型に変換してm_numに格納
Roman_int::Roman_int(string s){
	int sum = 0, tmp = 0;
	map<int, char>::iterator it;

	for(int i = 0; i < s.size(); ++i){
		for(map<int, char>::iterator it = romanintlist.begin(); it != romanintlist.end(); ++it){
			if(s[i] == it->second){
				if(tmp < it->first && i != 0){	// IV(9)など減算のパターンの場合
					sum += it->first - tmp - tmp;
					tmp = numeric_limits<int>::max();
				}
				else{							// 通常の場合
					sum += it->first;	
					tmp = it->first;			
				}
				break;
			}
		}
	}
	m_num = sum;
}

istream& operator>>(istream& is, Roman_int& r){
	string tmp;
	is >> tmp;
	if(!is) return is;
	r = Roman_int(tmp);
	return is;
}

ostream& operator<<(ostream& os, Roman_int& r){
	int tmp = r.as_int();
	while(tmp > 0){
		for(map<int, string>::reverse_iterator it = intromanlist.rbegin(); it != intromanlist.rend(); ++it){
			if(tmp - it->first >= 0){	
				os << it->second;
				tmp -= it->first;
				break;
			}
		}
	}
	return os;
}

int main(){
	init_romanintlist(romanintlist);
	init_intromanlist(intromanlist);

	Roman_int r;
	cout << "ローマ数字を入力してください > ";
	cin >> r;
	cout << "Roman " << r << " equals " << r.as_int() << '\n';
}