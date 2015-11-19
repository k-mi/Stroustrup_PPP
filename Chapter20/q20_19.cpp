#include <iostream>
using namespace std;

// 範囲チェック付きの双方向リンクリスト
template<class Elem> struct Link{
	Link(const Elem& v = Elem(), Link* p = nullptr, Link* s = nullptr)
		: val(v), prev(p), succ(s) { }

	Link* prev;	// 先行（前）リンク
	Link* succ;	// 後続（次）リンク
	Elem val;	// 値
};

template<class Elem> class list{
public:
	// デフォルトコンストラクタ
	// 末尾の要素の1つ後を表すためのLinkであるlastを割り当てる
	list() : first(new Link<Elem>()), last(first) { }

	class iterator; 		// 範囲チェック無しイテレータ
	class check_iterator;	// 範囲チェック付きイテレータ

	iterator begin(){ return iterator(first); }	// 最初の要素のイテレータ
	iterator end(){ return iterator(last); } 	// 最後の要素の1つ後のイテレータ
	check_iterator c_begin() { return check_iterator(begin(), begin(), end()); }
	check_iterator c_end() { return check_iterator(end(), begin(), end()); }

	iterator insert(iterator p, const Elem& v);	// リストのpの後（1つ前の要素?）にvを挿入する
	iterator erase(iterator p);					// リストからpを削除する

	void push_back(const Elem& v);	// vを最後に挿入する
	void push_front(const Elem& v);	// vを最初に挿入する
	void pop_front();				// 最初の要素を削除する
	void pop_back();				// 最後の要素を削除する

	Elem& front() { return first->val; }	// 最初の要素
	Elem& back(){ return last->prev->val; }	// 最後の要素	

private:
	Link<Elem>* first;
	Link<Elem>* last;	// 最後のリンクの1つ後
};

template<class Elem> class list<Elem>::iterator{
public:
	iterator(Link<Elem>* p) : curr(p) { }
	iterator& operator++() { curr = curr->succ; return *this; }	// 前方
	iterator& operator--() { curr = curr->prev; return *this; }	// 後方
	Elem& operator*() { return curr->val; }		// 値を取得する（間接参照）

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }

	Link<Elem>* current() { return curr; }

private:
	Link<Elem>* curr;	// 現在のリンク
};

// 範囲チェック付きイテレータ
template<class Elem> class list<Elem>::check_iterator{
public:
	check_iterator(iterator p, iterator f, iterator e)
		: curr(p), first(f), end(e) { }

	check_iterator& operator++() {
		if(++curr == end) throw out_of_range("++");
		return *this; 
	}
	check_iterator& operator--() {
		if(curr == first) throw out_of_range("--");
		--curr;
		return *this; 
	}

	bool operator==(const check_iterator& it) const { return curr == it.curr; }
	bool operator!=(const check_iterator& it) const { return curr != it.curr; }

	Elem& operator*() { return *curr; }		// 値を取得する（間接参照）
	iterator current() { return curr; }		// 現在のイテレータを取得する

private:
	iterator curr;	// 現在のイテレータ
	iterator first;	// 最初のイテレータ
	iterator end;	// 最後のイテレータ
};

// リストのpの後（1つ前の要素?）にvを挿入し、挿入した要素のイテレータを返す
template<class Elem> class list<Elem>::iterator list<Elem>::insert(iterator p , const Elem& v){
	Link<Elem>* newlink = new Link<Elem>(v, p.current()->prev, p.current());
	if(p == begin()) first = newlink;			// 最初の要素を変更
	newlink->succ->prev = newlink;
	if(newlink->prev != nullptr) newlink->prev->succ = newlink;
	return iterator(newlink);
}

// リストからpを削除し、1つ前の要素のイテレータを返す
template<class Elem> class list<Elem>::iterator list<Elem>::erase(iterator p){
	if(p == end()) return last;
	if(p == begin()) first = p.current()->succ;	// 最初の要素を変更
	if(p.current()->prev != nullptr) p.current()->prev->succ = p.current()->succ;
	p.current()->succ->prev = p.current()->prev;
	iterator tmp = --p;
	delete p.current();		// 削除
	return tmp;
}

// vを最後（end()の1つ前）に挿入する
template<class Elem> void list<Elem>::push_back(const Elem& v){
	insert(end(), v);
}

// vを最初（begin()の1つ前）に挿入する
template<class Elem> void list<Elem>::push_front(const Elem& v){
	insert(begin(), v);
}	

// 最初の要素（begin()）を削除する
template<class Elem> void list<Elem>::pop_front(){
	if(begin() != end())	// 要素がある場合のみ実行
		erase(begin());
}

// 最後の要素（end()の1つ前）を削除する
template<class Elem> void list<Elem>::pop_back(){
	if(begin() != end())	// 要素がある場合のみ実行
		erase(--end());
}

// 最も大きな値を持つ[first:last)の範囲内の要素へのイテレータを返す
template<class Iterator> Iterator high(Iterator first, Iterator last){
	Iterator high = first;
	for(Iterator p = first; p != last; ++p)
		if(*high < *p) high = p;
	return high;
}

int main(){
	try{
		int x;
		list<double> lst;

		while(cin >> x) lst.push_back(x);	// 入力

		// わざとイテレータを領域外に出す
		list<double>::check_iterator it = lst.c_begin();
		while(true){
			cout << *it << endl;
			++it;
		}
	}
	catch(out_of_range e){
		cerr << "Error: " << e.what() << endl;	// Error: ++
	}
}