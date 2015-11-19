#include <stdio.h>
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */

/* 双方向リンクリストのリンク */
struct Link{
	struct Link* pre;
	struct Link* suc;
};

struct List{
	struct Link* first;
	struct Link* last;
};

/* *lstを空のリストとして初期化する */
void init(struct List* lst){
	assert(lst);
	lst->first = lst->last = 0;
}

/* 空のリストを新規作成する */
struct List* create(){
	struct List* lst = (struct List*)malloc(sizeof(struct List));
	init(lst);
	return lst;
}

/* lstの要素をすべて解放する */
void clear(struct List* lst){
	assert(lst);
	{
		struct Link* curr = lst->first;
		while(curr){
			struct Link* next = curr->suc;
			free(curr);
			curr = next;
		}
		lst->first = lst->last = 0;
	}
}

/* lstの要素をすべて解放した後、lstを解放する */
void destroy(struct List* lst){
	assert(lst);
	clear(lst);
	free(lst);
}

/* pをlstの末尾に追加する */
void push_back(struct List* lst, struct Link* p){
	assert(lst);
	assert(p);

	{
		struct Link* last = lst->last;
		if(last){
			last->suc = p;	/* pをlastの後に追加する */
			p->pre = last;
		}
		else{
			lst->first = p;	/* pは最初の要素 */
			p->pre = 0;
		}
		lst->last = p;		/* pは新しい最後の要素 */
		p->suc = 0;
	}
}

/* lstの先頭にpを追加する */
void push_front(struct List* lst, struct Link* p){
	assert(lst);
	assert(p);

	{
		struct Link* first = lst->first;
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
}

/* lstのpの前にqを追加する */
void insert(struct List* lst, struct Link* p, struct Link* q){
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

/* lstからpを削除する pの後のリンクへのポインタを返す */
struct Link* erase(struct List* lst, struct Link* p){
	assert(lst);
	if(p == 0) return 0;	/* erase(0)はOK */

	if(p == lst->first){
		if(p->suc){
			lst->first = p->suc;	/* sucがfirstになる */
			p->suc->pre = 0;
			return p->suc;
		}
		else{
			lst->first = lst->last = 0;	/* リストは空になる */
			return 0;
		}
	}
	else if(p == lst->last){
		if(p->pre){
			lst->last = p->pre;		/* preがlastになる */
			p->pre->suc = 0;
			return p->suc;			/* 0を返す */
		}
		else{
			lst->first = lst->last = 0;	/* リストは空になる */
			return 0;
		}
	}
	else{
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

/* pから前方または後方にn個目のリンクを返す */
struct Link* advanece(struct Link* p, int n){
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

struct Name{
	struct Link lnk;	/* Listの操作に必要なLink */
	char* p;
};

struct Name* make_name(char* n){
	struct Name* p = (struct Name*)malloc(sizeof(struct Name));
	p->p = n;
	return p;
}

/* すべての名前を書き出す */
void print_list(struct List* lst){
	assert(lst);
	struct Link* curr = lst->first;
	int count = 0;
	for(; curr != 0; curr = curr->suc){
		count++;
		printf("element %d: %s\n", count, ((struct Name*)curr)->p);
	}
}

int main(){
	/* リストを作成する init()は関数内で呼び出される*/
	struct List* names = create();
	
	void* p;

	/* Nameをいくつか作成し、それらをリストに追加する */
	push_back(names, (struct Link*)make_name("Norah"));
	push_back(names, (struct Link*)make_name("Annemarie"));
	push_back(names, (struct Link*)make_name("Kris"));
	print_list(names);

	/* 2つ目のName（インデックス1）を削除する */
	p = advanece(names->first, 1);
	erase(names, (struct Link*)p);	
	free(p);
	print_list(names);

	/* 先頭に追加する */
	push_front(names, (struct Link*)make_name("Jun"));
	print_list(names);

	/* インデックス2にある要素の前にNameを追加する */
	p = advanece(names->first, 2);
	insert(names, (struct Link*)p, (struct Link*)make_name("Menma"));
	print_list(names);

	/* namesの要素をすべて削除した後、lstを解放する */
	destroy(names); /* clear()は関数内で呼び出される */

	return 0;
}