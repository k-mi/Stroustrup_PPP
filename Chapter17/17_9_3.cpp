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
	if(n == 0) return p;
	if(p == 0) return n;
	n->succ = p;			// pがnの次の要素になる
	if(p->prev != 0)		// pが先頭でない（pの前が存在する）場合のみ
		p->prev->succ = n;	// nがpの前の要素になる
	n->prev = p->prev;		// pの前の要素がnの前の要素になる
	p->prev = n;			// nがpの前の要素になる
	return n;
}

// nをpの後に挿入し、nを返す
Link* add(Link* p, Link* n){
	if(n == 0) return p;
	if(p == 0) return n;
	n->prev = p;
	if(p->succ != 0)
		p->succ->prev = n;
	n->succ = p->succ;
	p->succ = n;
	return n;
}

// リストから*pを削除し、pの次の要素を返す
Link* erase(Link* p){
	if(p == 0) return p;
	if(p->succ != 0)
		p->succ->prev = p->prev;
	if(p->prev != 0)
		p->prev->succ = p->succ;
	return p->succ;
}

// リストでsを検索する
// 見つからない場合は0を返す
Link* find(Link* p, const string& s){
	while(p){
		if(p->value == s) return p;
		p = p->succ;
	}
	return 0;
}

// リストをn位置移動する
// 見つからない場合は0を返す
// nが正の場合前方へ進み、負の場合は後方へ進む
Link* advance(Link* p, int n){
	if(p == 0) return p;
	if(n > 0){
		while(n--){	// 0になったら偽
			if(p->succ == 0) return 0;
			p = p -> succ;
		}
	}
	else if(n < 0){
		while(n++){	// 0になったら偽
			if(p->prev == 0) return 0;
			p = p -> prev;
		}
	}
	return p;
}

int main(){
	Link* norse_gods = new Link("Thor");
	norse_gods = insert(norse_gods, new Link("Odin"));
	norse_gods = insert(norse_gods, new Link("Freia"));
}