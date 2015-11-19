#include <iostream>
#include <string>
using namespace std;

struct Person{
	Person() { }
	Person(const string& n, int a) : name(n), age(a) { }

	string name;
	int age;
};

istream& operator>>(istream& is, Person& p){
	is >> p.name >> p.age;
	return is;
}

ostream& operator<<(ostream& os, Person& p){
	if(!os) return os;

	os << p.name << ' ' << p.age;
	return os;
}

int main(){
	Person p;

	cin >> p;
	cout << p << endl;
}