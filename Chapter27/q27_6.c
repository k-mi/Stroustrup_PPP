#include <stdio.h>
#include <stdlib.h>	/* malloc, free */
#include <assert.h>	/* assert */

#define LINK_MAX 100

/* 双方向リンクリストのリンク */
struct Link{
	int pre;
	int suc;
};

struct List{
	int first;
	int last;
	struct Link* links[LINK_MAX];
};

/* *lstを空のリストとして初期化する */
void init(struct List* lst){
	assert(lst);

	lst->first = lst->last = -1;
	{
		/* linksの全要素をNULLにする */
		int i = 0;
		for(; i < LINK_MAX; ++i) lst->links[i] = 0;
	}
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
		int curr = lst->first;
		while(curr != -1){
			int tmp = lst->links[curr]->suc;
			free(lst->links[curr]);
			curr = tmp;
		}
		lst->first = lst->last = -1;
	}
}

/* lstの要素をすべて解放した後、lstを解放する */
void destroy(struct List* lst){
	assert(lst);
	clear(lst);
	free(lst);
}

/* 空いている要素のインデックスを返す */
int empty_element(struct List* lst){
	int i = 0;
	while(i < LINK_MAX){
		if(lst->links[i] == 0) return i;
		++i;
	}
	return -1;
}

/* pをlstの末尾に追加する */
void push_back(struct List* lst, struct Link* p){
	assert(lst);
	assert(p);

	{
		int index = empty_element(lst);
		if(index == -1) return;	/* 配列に空きがない */
		lst->links[index] = p;
		if(lst->first == -1){	/* pは1つ目の要素 */
			lst->first = index;
			p->pre = -1;
		}
		else{					/* pをlastの後に追加する */
			lst->links[lst->last]->suc = index;
			p->pre = lst->last;
		}
		lst->last = index;
		p->suc = -1;
	}
}

/* lstの先頭にpを追加する */
void push_front(struct List* lst, struct Link* p){
	assert(lst);
	assert(p);

	{
		int index = empty_element(lst);
		if(index == -1) return;	/* 配列に空きがない */
		lst->links[index] = p;
		if(lst->first == -1){	/* pは1つ目の要素 */
			lst->last = index;
			p->suc = -1;
		}
		else{					/* pをfirstの前に追加する */
			lst->links[lst->first]->pre = index;
			p->suc = lst->first;
		}
		lst->first = index;
		p->pre = -1;
	}
}

/* lstのpの前にqを追加する */
void insert(struct List* lst, struct Link* p, struct Link* q){
	assert(lst);
	assert(q);

	if(p == lst->links[lst->first]){
		push_front(lst, p);
	}
	else if(p == 0){
		push_back(lst, p);
	}
	else{
		int index = empty_element(lst);
		if(index == -1) return;	/* 配列に空きがない */
		lst->links[index] = q;

		q->pre = p->pre;
		q->suc = lst->links[p->pre]->suc;
		lst->links[p->pre]->suc = index;
		p->pre = index;
	}
}

/* lstからpを削除する pの後のリンクへのポインタを返す */
struct Link* erase(struct List* lst, struct Link* p){
	assert(lst);
	if(p == 0) return 0;	/* erase(0)はOK */

	if(p == lst->links[lst->first]){
		if(lst->links[p->suc]){
			int index = lst->links[p->suc]->pre;
			lst->first = p->suc;	/* sucがfirstになる */
			lst->links[p->suc]->pre = -1;
			lst->links[index] = 0;
			return lst->links[p->suc];
		}
		else{
			clear(lst);	/* リストは空になる */
			return 0;
		}
	}
	else if(p == lst->links[lst->last]){
		if(lst->links[p->pre]){
			int index = lst->links[p->pre]->suc;
			lst->last = p->pre;		/* preがlastになる */
			lst->links[p->pre]->suc = -1;
			lst->links[index] = 0;
			return lst->links[p->suc];	/* 0を返す */
		}
		else{
			clear(lst);	/* リストは空になる */
			return 0;
		}
	}
	else{
		lst->links[p->suc]->pre = p->pre;
		lst->links[p->pre]->suc = p->suc;
		return lst->links[p->suc];
	}
}

/* pから前方または後方にn個目のリンクを返す */
/* そのままでは無理なのでインターフェイスを変更 */	
struct Link* advanece(struct List* lst, struct Link* p, int n){
	assert(lst);
	assert(p);

	if(n > 0){
		while(n > 0 && p->suc != -1){
			p = lst->links[p->suc];
			--n;
		}
	}
	else if(n < 0){
		while(n < 0 && p->pre != -1){
			p = lst->links[p->pre];
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

	{
		int count = 1;
		int curr = lst->first;
		while(curr != -1){
			printf("element %d: %s\n", count, ((struct Name*)(lst->links[curr]))->p);
			curr = lst->links[curr]->suc;
			++count;
		}
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
	p = advanece(names, names->links[names->first], 1);
	erase(names, (struct Link*)p);	
	free(p);
	print_list(names);

	/* インデックス2にある要素の前にNameを追加する */
	p = advanece(names, names->links[names->first], 2);
	insert(names, (struct Link*)p, (struct Link*)make_name("Menma"));
	print_list(names);

	/* 先頭に追加する */
	push_front(names, (struct Link*)make_name("Jun"));
	print_list(names);

	/* namesの要素をすべて削除した後、lstを解放する */
	destroy(names); /* clear()は関数内で呼び出される */

	return 0;
}