#include <iostream>
using namespace std;

struct Link{
	string value;
	Link* prev;
	Link* succ;
	Link(const string& v, Link* p = 0, Link* s = 0)
		: value(v), prev(p), succ(s) { }
};

// nをpの前に挿入し、nを返す
Link* insert(Link* p, Link* n){
	if (n == 0) return p;
	if (p == 0) return n;
	n->succ = p;			// pがnの次の要素になる
	if(p->prev != 0)		// pが先頭でない（pの前が存在する）場合のみ
		p->prev->succ = n;	// nがpの前の要素になる
	n->prev = p->prev;		// pの前の要素がnの前の要素になる
	p->prev = n;			// nがpの前の要素になる
	return n;
}

int main(){
	Link* norse_gods = new Link("Thor");
	norse_gods = insert(norse_gods, new Link("Odin"));
	norse_gods = insert(norse_gods, new Link("Freia"));
}