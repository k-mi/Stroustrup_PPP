#include <iostream>
using namespace std;

struct Link{
	string value;
	Link* prev;
	Link* succ;
	Link(const string& v, Link* p = 0, Link* s = 0)
		: value(v), prev(p), succ(s) { }
};

int main(){
	Link* norse_gods = new Link("Thor", 0, 0);
	norse_gods = new Link("Oden", 0, norse_gods);
	norse_gods -> succ -> prev = norse_gods;
	norse_gods = new Link("Freia", 0, norse_gods);
	norse_gods -> succ -> prev = norse_gods;
}