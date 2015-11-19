#include <iostream>
using namespace std;

// 単方向リスト
class Link{
public:
	string value;

	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), succ(s) { }

	Link* add(Link* n);				// nをこのオブジェクトの後の挿入
	Link* find(const string& s); 	// リストでsを検索
	const Link* find(const string& s) const;	// constリストでsを検索(18.4.1)
	Link* advance(int n) const;		// リストをn位置移動
	Link* next() const { return succ; }

private:
	Link* succ;
};

// nをこのオブジェクト(this)の後に挿入し、nを返す
Link* Link::add(Link* n){
	if(n == nullptr) return this;
	Link* tmp = succ;
	succ = n;
	n->succ = tmp;
	return n;
}

// リストでsを検索する
// 見つからない場合はnullptrを返す
Link* Link::find(const string& s){
	Link* p = this;
	while(p){
		if(p->value == s) return p;
		p = p->succ;
	}
	return 0;
}

// constリストでsを検索する
// 見つからない場合は0を返す
const Link* Link::find(const string& s) const{
	const Link* p = this;
	while(p){
		if(p->value == s) return p;
		p = p->succ;
	}
	return nullptr;
}

// リストをn位置移動する
// 見つからない場合か（n<=0）の場合はnullptrを返す
Link* Link::advance(int n) const{
	if(n <= 0) return nullptr;
	else{
		n--;
		Link* p = succ;
		while(n--){	// 0になったら偽
			if(p == nullptr) return nullptr;
			p = p -> succ;
		}
		return p;
	}
}

void print_all(Link* p){
	cout << "{ ";
	while(p){
		cout << p->value;
		if((p = p->next())) cout << ", ";
	}
	cout << " }";
}

void erase_all(Link* p){
	Link* tmp = nullptr;
	do {
		tmp = p->next();
		delete p;
		p = tmp;
	} while(p);
}

int main(){
	Link* norse_gods = new Link("Thor");
	norse_gods->add(new Link("Odin"));
	norse_gods->add(new Link("Freia"));

	Link* greek_gods = new Link("Hera");
	greek_gods->add(new Link("Athena"));
	greek_gods->add(new Link("Mars"));
	greek_gods->add(new Link("Poseidon"));
	greek_gods->add(new Link("Zeus"));

	Link* p = greek_gods->find("Mars");
	if(p != nullptr) p->value = "Ares";

	print_all(norse_gods);
	cout << endl;
	print_all(greek_gods);
	cout << endl;
}