#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// charsの文字が文字列sに含まれているか
bool is_chars(const string& s, const string& chars){
	for(int i = 0; i < chars.size(); ++i){
		string::size_type n = s.find(chars[i]);
		if(n == string::npos) continue;
		else return true;
	}
	return false;
}

class Person{
public:
	Person(const string& fn, const string& sn, int a) : m_fname(fn), m_sname(sn), m_age(a) {
		if(0 > m_age || m_age >= 150) throw runtime_error("Bad age");	// error関数の代用
		if(m_fname == "" || is_chars(m_fname, "\"'[]*&^%$#@!")) throw runtime_error("Bad first_name");
		if(m_sname == "" || is_chars(m_sname, "\"'[]*&^%$#@!")) throw runtime_error("Bad second_name");
	}

	string first_name() const { return m_fname; }
	string second_name() const { return m_sname; }
	int age() const { return m_age; }

private:
	string m_fname;	// firstname
	string m_sname;	// secondname
	int m_age;
};

istream& operator>>(istream& is, Person& p){
	string fname, sname;
	int age;

	is >> fname >> sname >> age;
	p = Person(fname, sname, age);

	return is;
}

ostream& operator<<(ostream& os, const Person& p){
	if(!os) return os;

	os << p.first_name() << ' ' << p.second_name() << ' ' << p.age();
	return os;
}

int main(){
	Person tmp("Dummy", "Unkown", 0);

	cin >> tmp;
	cout << tmp << endl;
}