class Link{
public:
	string value;

	Link(const string& v, Link* p = 0, Link* s = 0)
		: value(v), prev(p), succ(s) { }

	Link* insert(Link* n);			// nをこのオブジェクトの前に挿入
	Link* add(Link* n);				// nをこのオブジェクトの前の挿入
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

// nをpの前に挿入し、nを返す
Link* Link::insert(Link* n){
	Link* p = this;			// このオブジェクト(this)へのポインタ
	if(n == 0) return p;	// 何も挿入しない
	if(p == 0) return n;	// 何も挿入しない
	n->succ = p;			// pがnの次の要素になる
	if(p->prev != 0)		// pが先頭でない（pの前が存在する）場合のみ
		p->prev->succ = n;	// nがpの前の要素になる
	n->prev = p->prev;		// pの前の要素がnの前の要素になる
	p->prev = n;			// nがpの前の要素になる
	return n;
}