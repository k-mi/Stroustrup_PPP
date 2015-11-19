#include <iostream>
using namespace std;

// 双方向リスト
class Link{
public:
	string value;

	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), prev(p), succ(s) { }

	Link* insert(Link* n);			// nをこのオブジェクトの前に挿入
	Link* add(Link* n);				// nをこのオブジェクトの後の挿入
	Link* erase();					// リストからこのオブジェクトを削除
	Link* find(const string& s); 	// リストでsを検索
	const Link* find(const string& s) const;	// constリストでsを検索(18.4.1)
	Link* advance(int n) const;		// リストをn位置移動
	Link* next() const { return succ; }
	Link* previous() const { return prev; }

private:
	Link* prev;
	Link* succ;
};

// nをこのオブジェクト(this)の前に挿入し、nを返す
Link* Link::insert(Link* n){
	if(n == nullptr) return this;	// 何も挿入しない
	n->succ = this;			// thisがnの次の要素になる
	if(prev != nullptr)		// thisが先頭でない（thisの前が存在する）場合のみ
		prev->succ = n;		// nがthisの前の要素になる
	n->prev = prev;			// thisの前の要素がnの前の要素になる
	prev = n;				// nがthisの前の要素になる
	return n;
}

// nをこのオブジェクト(this)の後に挿入し、nを返す
Link* Link::add(Link* n){
	if(n == nullptr) return this;
	n->prev = this;
	if(succ != nullptr)
		succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

// リストからこのオブジェクトを削除し、次の要素を返す
Link* Link::erase(){
	if(succ != nullptr)
		succ->prev = prev;
	if(prev != nullptr)
		prev->succ = succ;
	return succ;
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
// 見つからない場合か自身（n==0）の場合はnullptrを返す
// nが正の場合前方へ進み、負の場合は後方へ進む
Link* Link::advance(int n) const{
	if(n == 0) return nullptr;
	else if(n > 0){
		n--;
		Link* p = succ;
		while(n--){	// 0になったら偽
			if(p == nullptr) return nullptr;
			p = p -> succ;
		}
		return p;
	}
	else{
		n++;
		Link* p = prev;
		while(n++){	// 0になったら偽
			if(p == nullptr) return nullptr;
			p = p -> prev;
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
	norse_gods = norse_gods->insert(new Link("Odin"));
	norse_gods = norse_gods->insert(new Link("Zeus"));
	norse_gods = norse_gods->insert(new Link("Freia"));

	Link* greek_gods = new Link("Hera");
	greek_gods = greek_gods->insert(new Link("Athena"));
	greek_gods = greek_gods->insert(new Link("Mars"));
	greek_gods = greek_gods->insert(new Link("Poseidon"));

	Link* p = greek_gods->find("Mars");
	if(p != nullptr) p->value = "Ares";

	Link* p2 = norse_gods->find("Zeus");
	if(p2 != nullptr){
		if(p2 == norse_gods)	// 先頭を削除する場合ポインタを次に移す 
			norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->insert(p2);
	}

	print_all(norse_gods);
	cout << endl;
	print_all(greek_gods);
	cout << endl;

	erase_all(norse_gods);
	erase_all(greek_gods);
}