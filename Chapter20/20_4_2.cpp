template<class Elem> class list{
	// 表現および実装上の詳細
public:
	class iterator; 	// メンバの型: iterator

	iterator begin();	// 最初の要素のイテレータ
	iterator end(); 	// 最後の要素の1つ後のイテレータ

	iterator insert(iterator p, const Elem& v);	// リストのpの後にvを挿入する
	iterator erase(iterator p);					// リストからpを削除する

	void push_back(const Elem& v);	// vを最後に挿入する
	void push_front(const Elem& v);	// vを最初に挿入する
	void pop_front();	// 最初の要素を削除する
	void pop_back();	// 最後の要素を削除する

	Elem& front();		// 最初の要素
	Elem& back();		// 最後の要素

	// ...	
};

template<class Elem> class list<Elem>::iterator{
public:
	iterator(Link<Elem>* p) : curr(p) { }
	iterator& operator++() { curr = curr->succ; return *this; }	// 前方
	iterator& operator--() { curr = curr->prev; return *this; }	// 後方
	Elem& operator*() { return curr->val; }		// 値を取得する（間接参照）

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }

private:
	Link<Elem>* curr;	// 現在のリンク
};

// 最も大きな値を持つ[first:last)の範囲内の要素へのイテレータを返す
template<class Iterator> 
Iterator high(Iterator first, Iterator last){
	Iterator high = first;
	for(Iterator p = first; p != last; ++p)
		if(*high < *p) high = p;
	return high;
}

void f(){
	list<int> lst;
	int x;
	while(cin >> x) lst.push_front(x);

	list<int>::iterator p = high(lst.begin(). lst.end());
	cout << "the highest value was " << *p << endl;
}