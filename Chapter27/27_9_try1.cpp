#include <iostream>
#include <cassert>	// assert
using namespace std;

// 双方向リンクリストのリンク
struct Link{
	Link* pre;
	Link* suc;
};

struct List{
	List() : first(0), last(0) { }	// init: 空のリストとして初期化する
	Link* first;
	Link* last;
};

// 空のリストを新規作成する
List* create(){
	List* lst = new List;
	return lst;
}

// lstの要素をすべて解放する
void clear(struct List* lst){
	assert(lst);

	Link* curr = lst->first;
	while(curr){
		Link* next = curr->suc;
		delete curr;
		curr = next;
	}
	lst->first = lst->last = 0;
}

// lstの要素をすべて解放した後、lstを解放する
void destroy(List* lst){
	assert(lst);
	clear(lst);
	delete lst;
}

// pをlstの末尾に追加する
void push_back(List* lst, Link* p){
	assert(lst);
	assert(p);

	Link* last = lst->last;
	if(last){
		last->suc = p;	// pをlastの後に追加する
		p->pre = last;
	}
	else{
		lst->first = p;	// pは最初の要素
		p->pre = 0;
	}
	lst->last = p;		// pは新しい最後の要素
	p->suc = 0;
}

// lstの先頭にpを追加する
void push_front(List* lst, Link* p){
	assert(lst);
	assert(p);

	Link* first = lst->first;
	if(first){
		first->pre = p;
		p->suc = first;		
	}
	else{
		lst->last = p;
		p->suc = 0;
	}
	lst->first = p;
	p->pre = 0;
}

// lstのpの前にqを追加する
void insert(List* lst, Link* p, Link* q){
	assert(lst);
	assert(q);

	if(p == lst->first){
		push_front(lst, p);
	}
	else if(p == 0){
		push_back(lst, p);
	}
	else{
		q->pre = p->pre;
		q->suc = p;
		p->pre->suc = q;
		p->pre = q;
	}
}

// lstからpを削除する pの後のリンクへのポインタを返す
Link* erase(List* lst, Link* p){
	assert(lst);
	if(p == 0) return 0;	// erase(0)はOK

	if(p == lst->first){
		if(p->suc){
			lst->first = p->suc;	// sucがfirstになる
			p->suc->pre = 0;
			return p->suc;
		}
		else{
			lst->first = lst->last = 0;	// リストは空になる
			return 0;
		}
	}
	else if(p == lst->last){
		if(p->pre){
			lst->last = p->pre;		// preがlastになる
			p->pre->suc = 0;
			return p->suc;			// 0を返す
		}
		else{
			lst->first = lst->last = 0;	// リストは空になる
			return 0;
		}
	}
	else{
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

// pから前方または後方にn個目のリンクを返す
Link* advanece(Link* p, int n){
	if(n > 0){
		while(n > 0 && p){
			p = p->suc;
			--n;
		}
	}
	else if(n < 0){
		while(n < 0 && p){
			p = p->pre;
			++n;
		}
	}
	return p;
}

struct Name : Link{
	Name(char* pp) : p(pp) { }
	char* p;
};

Name* make_name(const string& n){
	return new Name(const_cast<char*>(n.c_str()));
}

int main(){
	List names;	// リストを作成する

	// Nameをいくつか作成し、それらをリストに追加する
	push_back(&names, static_cast<Link*>(make_name("Norah")));
	push_back(&names, static_cast<Link*>(make_name("Annemarie")));
	push_back(&names, static_cast<Link*>(make_name("Kris")));

	// 2つ目の名前（インデックス1）を削除する
	erase(&names, advanece(names.first, 1));

	int count = 0;
	for(Link* curr = names.first; curr != 0; curr = curr->suc){	// すべての名前を書き出す
		count++;
		cout << "element " << count << ": " << static_cast<Name*>(curr)->p << endl;
	}
}