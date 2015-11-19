#include <iostream>
#include <string>
using namespace std;

struct Person{
	string name;
	int age;
};

int main(){
	Person p;
	p.name = "Goofy";
	p.age = 63;

	cout << p.name << ' ' << p.age << endl;
}