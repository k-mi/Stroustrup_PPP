#include <stdio.h>
#include <stdlib.h>	/* calloc, free */
#include <string.h>	/* strcmp, memcpy */

/* Tableの内部データ */
struct Pair{
	const char* key;		/* 要素のキー */
	int val;				/* 要素の値 */
};

/* 順序付けされていないPair(Cスタイルのstring、int)のテーブル */
struct Table{
	struct Pair* pair;
	int size;			/* pairの要素数 */
	int space;			/* pair用に確保した要素数 */	
};

/* Tableを初期化 */
void init(struct Table* table){
	table->size = 0;
	table->space = 8;
	table->pair = (struct Pair*)calloc(table->space, sizeof(struct Pair));
}

/* メモリを解放してTableを破棄 */
void destroy(struct Table* table){
	free(table->pair);
	table->size = 0;
	table->space = 0;
}

/* tableからkeyを検索してその要素へのポインタを返す。
   見つからない場合は0（ヌルポインタ）を返す。 */
struct Pair* find(struct Table* table, const char* key){
	int i;
	
	for(i = 0; i < table->size; ++i){
		if(table->pair[i].key != 0 && strcmp(table->pair[i].key, key) == 0){
			return &(table->pair[i]);
		}
	}
	return 0;
}

/* tableにPairの要素（key, val）を挿入 */
void insert(struct Table* table, const char* key, int val){
	struct Pair* p = find(table, key);
	if(p){
		p->val = val;	/* すでにkeyが存在していれば、valを変更するだけ */
	}
	else{
		int i;
		for(i = 0; i < table->size; ++i)	/* 空の要素の存在するか　*/
			if(table->pair[i].key == 0) break;

		/* 要素を拡張 */
		if(table->size + 1 >= table->space){	
			struct Pair* tmp = (struct Pair*)calloc(table->space * 2, sizeof(struct Pair));
			memcpy(tmp, table->pair, table->space);
			free(table->pair);
			table->pair = tmp;
			table->space *= 2;
		}

		/* 要素を挿入 */
		table->pair[i].key = key;
		table->pair[i].val = val;
		++(table->size);
	}
}

/* tableからkeyをキーに持つ要素を削除する。
   stdio.hにremove関数が存在するため、remove2に更変更 */
void remove2(struct Table* table, const char* key){
	struct Pair* p = find(table, key);
	if(p){	/* 要素が存在する場合のみ */
		p->key = 0;
		--(table->size);
	}
}

int main(){
	struct Table table;
	struct Pair* p;

	/* 初期化 */
	init(&table);

	/* 挿入　*/
	insert(&table, "apple", 10);
	insert(&table, "banana", 15);
	insert(&table, "chocolate", 5);

	/* 検索　*/
	p = find(&table, "banana");
	if(p != 0) printf("%s: %d\n", p->key, p->val);	
	p = find(&table, "app");
	if(p != 0) printf("%s: %d\n", p->key, p->val);	/* 表示されない */

	/* 削除 */
	remove2(&table, "banana");
	p = find(&table, "banana");
	if(p != 0) printf("%s: %d\n", p->key, p->val);	/* 表示されない */	

	/* 変更 */
	insert(&table, "chocolate", 999);
	p = find(&table, "chocolate");
	if(p != 0) printf("%s: %d\n", p->key, p->val);
	p->val = 12345;	
	p = find(&table, "chocolate");
	if(p != 0) printf("%s: %d\n", p->key, p->val);

	/* 破棄 */
	destroy(&table);
}