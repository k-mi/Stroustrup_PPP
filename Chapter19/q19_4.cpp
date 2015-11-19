#include <iostream>
#include <string>
using namespace std;

struct God{
	God(string n, string m, string v, string w) 
		: name(n), mythology(m), vehicle(v), weapon(w) { }

	string key() { return name; }	// ここで指定した値を元にソートを行う

	string name;		// 名前
	string mythology;	// 神話
	string vehicle;		// 乗り物
	string weapon;		// 武器
};

ostream& operator<<(ostream& os, const God& g){
	if(!os) return os;
	os << g.name << ' ' << g.mythology << ' ' << g.vehicle << ' ' << g.weapon;
	return os;
}

template<class T> class Link{
public:
	T value;

	Link(const T& v, Link* p = nullptr, Link* s = nullptr)
		: value(v), prev(p), succ(s) { }

	Link* insert(Link* n);			// nをこのオブジェクトの前に挿入
	Link* add(Link* n);				// nをこのオブジェクトの後の挿入
	Link* add_ordered(Link* n); 	// nを名前の辞書式順序で正しい位置に挿入
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
template<class T> Link<T>* Link<T>::insert(Link* n){
	if(n == nullptr) return this;	// 何も挿入しない
	n->succ = this;			// thisがnの次の要素になる
	if(prev != nullptr)		// thisが先頭でない（thisの前が存在する）場合のみ
		prev->succ = n;		// nがthisの前の要素になる
	n->prev = prev;			// thisの前の要素がnの前の要素になる
	prev = n;				// nがthisの前の要素になる
	return n;
}

// nをこのオブジェクト(this)の後に挿入し、nを返す
template<class T> Link<T>* Link<T>::add(Link* n){
	if(n == nullptr) return this;
	n->prev = this;
	if(succ != nullptr)
		succ->prev = n;
	n->succ = succ;
	succ = n;
	return n;
}

// nを名前の辞書式順序で正しい位置に挿入し、先頭要素を返す
template<class T> Link<T>* Link<T>::add_ordered(Link* n){
	if(n == nullptr || n->value.key() == "") return this;

	Link* p = this;
	if(p->value.key() > n->value.key()) return p->insert(n);

	do{
		p = p->succ;
		if(p->value.key() > n->value.key()){
			p->insert(n);				
			return this;
		}
	} while(p->succ != nullptr);

	p->add(n);
	return this;
}

// リストからこのオブジェクトを削除し、次の要素を返す
template<class T> Link<T>* Link<T>::erase(){
	if(succ != nullptr)
		succ->prev = prev;
	if(prev != nullptr)
		prev->succ = succ;
	return succ;
}

// リストでsを検索する
// 見つからない場合はnullptrを返す
template<class T> Link<T>* Link<T>::find(const string& s){
	Link* p = this;
	while(p){
		if(p->value.key() == s) return p;
		p = p->succ;
	}
	return 0;
}

// constリストでsを検索する
// 見つからない場合は0を返す
template<class T> const Link<T>* Link<T>::find(const string& s) const{
	const Link* p = this;
	while(p){
		if(p->value.key() == s) return p;
		p = p->succ;
	}
	return nullptr;
}

// リストをn位置移動する
// 見つからない場合か自身（n==0）の場合はnullptrを返す
// nが正の場合前方へ進み、負の場合は後方へ進む
template<class T> Link<T>* Link<T>::advance(int n) const{
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

template<class T> void print_all(Link<T>* p){
	while(p){
		cout << p->value;
		if((p = p->next())) cout << endl;
	}
	cout << endl;
}

template<class T> void erase_all(Link<T>* p){
	Link<T>* tmp = nullptr;
	do {
		tmp = p->next();
		delete p;
		p = tmp;
	} while(p);
}

int main(){
	Link<God>* gods = new Link<God>(God("Odin", "Norse", "Eight-legged flying horse called Sleipner", ""));
	gods = gods->add_ordered(new Link<God>(God("Freia", "Norse", "", "")));
	gods = gods->add_ordered(new Link<God>(God("Poseidon", "Greek", "", "")));
	gods = gods->add_ordered(new Link<God>(God("Zeus", "Greek", "", "lightning")));
	gods = gods->add_ordered(new Link<God>(God("Yamatanoorochi", "Japanese", "", "Serpentes")));

	cout << "Gods: " << endl;
	print_all(gods);
	cout << endl;

	// リストへ移動
	Link<God>* norse_gods = nullptr;
	Link<God>* greek_gods = nullptr;
	Link<God>* japanese_gods = nullptr;
	Link<God>* p = gods;
	while(p){
		if(p->value.mythology == "Norse"){
			if(norse_gods == nullptr) norse_gods = new Link<God>(p->value);
			else norse_gods->add(new Link<God>(p->value));
		}
		else if(p->value.mythology == "Greek"){
			if(greek_gods == nullptr) greek_gods = new Link<God>(p->value);
			else greek_gods->add(new Link<God>(p->value));
		}
		else{	// japanese
			if(japanese_gods == nullptr) japanese_gods = new Link<God>(p->value);
			else japanese_gods->add(new Link<God>(p->value));
		}
		p = p->next();
	}

	erase_all(gods);

	cout << "Norse Gods: " << endl;
	print_all(norse_gods);
	cout << endl;

	cout << "Greek Gods: " << endl;
	print_all(greek_gods);
	cout << endl;

	cout << "Japanese Gods: " << endl;
	print_all(japanese_gods);

	erase_all(norse_gods);
	erase_all(greek_gods);
	erase_all(japanese_gods);
}