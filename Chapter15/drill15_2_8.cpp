#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

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
	Person(const string& n, int a) : m_name(n), m_age(a) {
		if(0 > m_age || m_age >= 150) throw runtime_error("Bad age");	// error関数の代用
		if(is_chars(m_name, "\"'[]*&^%$#@!")) throw runtime_error("Bad name");
	}

	string name() const { return m_name; }
	int age() const { return m_age; }

private:
	string m_name;
	int m_age;
};

istream& operator>>(istream& is, Person& p){
	string name;
	int age;

	is >> name >> age;
	p = Person(name, age);

	return is;
}

ostream& operator<<(ostream& os, const Person& p){
	if(!os) return os;

	os << p.name() << ' ' << p.age();
	return os;
}

int main(){
	vector<Person> vp;
	Person tmp("Goofy", 63);

	for(int i = 0; i < 3; ++i){
		cin >> tmp;
		vp.push_back(tmp);
	}
		
	for(int i = 0; i < vp.size(); ++i)
		cout << vp[i] << endl;
}