#include <iostream>
#include <string>
using namespace std;

class Person{
public:
	Person(const string& n, int a) : m_name(n), m_age(a) { }

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
	Person p("Goofy", 63);
	cin >> p;

	cout << p << endl;
}