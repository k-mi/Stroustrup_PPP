#include <iostream>
#include <stdexcept>	// runtime_error
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
	if(lst == 0) throw runtime_error("null List* lst");

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
	if(lst == 0) throw runtime_error("null List* lst");
	clear(lst);
	delete lst;
}

// pをlstの末尾に追加する
void push_back(List* lst, Link* p){
	if(lst == 0) throw runtime_error("null List* lst");
	if(p == 0) throw runtime_error("null Link* p");

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
	if(lst == 0) throw runtime_error("null List* lst");
	if(p == 0) throw runtime_error("null Link* p");

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
	if(lst == 0) throw runtime_error("null List* lst");
	if(q == 0) throw runtime_error("null Link* q");

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
	if(lst == 0) throw runtime_error("null List* lst");
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

Link* make_name(const string& n){
	return static_cast<Link*>(new Name(const_cast<char*>(n.c_str())));
}

// すべての名前を書き出す
void print_list(List* list){
	if(list == 0) throw runtime_error("null List* list");

	Link* curr = list->first;
	int count = 0;
	for(; curr != 0; curr = curr->suc){
		count++;
		cout << "element " << count << ": " << static_cast<Name*>(curr)->p << endl;
	}
}

int main(){
	try{
		List* names = new List;	// リストを作成する

		// Nameをいくつか作成し、それらをリストに追加する
		push_back(names, make_name("Norah"));
		push_back(names, make_name("Annemarie"));
		push_back(names, make_name("Kris"));
		print_list(names);

		// 2つ目のName（インデックス1）を削除する
		Link* p = advanece(names->first, 1);
		erase(names, p);	
		delete static_cast<Name*>(p);

		// 先頭に追加する
		push_front(names, make_name("Jun"));
		print_list(names);

		// インデックス2にある要素の前にNameを追加する
		insert(names, advanece(names->first, 2), make_name("Menma"));
		print_list(names);

		// namesの要素をすべて削除した後、lstを解放する
		destroy(names);
	}
	catch(runtime_error& e){
		cerr << e.what() << endl;
	}
}