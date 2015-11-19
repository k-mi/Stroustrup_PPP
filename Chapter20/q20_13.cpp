#include <iostream>
using namespace std;

// 双方向リンクリスト（末尾の1つ後をnullptrで表す）
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
	// 末尾の要素の1つ後を表すためにnullptrを用いる
	list() : first(nullptr) { }

	class iterator; 	// メンバの型: iterator

	iterator begin(){ return iterator(first); }	// 最初の要素のイテレータ
	iterator end(){	return iterator(nullptr); } // 最後の要素の1つ後のイテレータ
	iterator back_it();							// 最後の要素のイテレータ

	iterator insert(iterator p, const Elem& v);	// リストのpの後（1つ前の要素?）にvを挿入する
	iterator erase(iterator p);					// リストからpを削除する

	void push_back(const Elem& v);	// vを最後に挿入する
	void push_front(const Elem& v);	// vを最初に挿入する
	void pop_front();				// 最初の要素を削除する
	void pop_back();				// 最後の要素を削除する

	Elem& front() { return first->val; }	// 最初の要素
	Elem& back();							// 最後の要素	

private:
	Link<Elem>* first;
};

template<class Elem> class list<Elem>::iterator{
public:
	iterator(Link<Elem>* p) : curr(p) { }

	// end()はヌルポインタであるため演算子使用不可
	iterator& operator++() { curr = curr->succ; return *this; }	// 前方
	iterator& operator--() { curr = curr->prev; return *this; } // 後方
	Elem& operator*() { return curr->val; }		// 値を取得する（間接参照）

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }

	Link<Elem>* current() { return curr; }

private:
	Link<Elem>* curr;	// 現在のリンク
};

// 最後の要素のイテレータを返す（q20_13で追加、低速注意）
template<class Elem> class list<Elem>::iterator list<Elem>::back_it(){
	iterator tmp = begin();
	for(iterator it = begin(); it != end(); ++it) { tmp = it; }
	return tmp;
}

// リストのpの後（1つ前の要素?）にvを挿入し、挿入した要素のイテレータを返す
template<class Elem> class list<Elem>::iterator list<Elem>::insert(iterator p , const Elem& v){
	Link<Elem>* newlink;
	if(first != nullptr && p == end()){	// 最後に追加する場合
		Link<Elem>* b = back_it().current();
		b->succ = newlink = new Link<Elem>(v, b, nullptr);
	}
	else{
		newlink = new Link<Elem>(v, first == nullptr ? nullptr : p.current()->prev, p.current());
		if(p == begin()) first = newlink;	// 最初の要素を変更
		if(newlink->succ != nullptr) newlink->succ->prev = newlink;
		if(newlink->prev != nullptr) newlink->prev->succ = newlink;		
	}
	return iterator(newlink);
}

// リストからpを削除し、1つ前の要素のイテレータを返す
template<class Elem> class list<Elem>::iterator list<Elem>::erase(iterator p){
	if(p == end()) return p;
	if(p == begin()) first = p.current()->succ;	// 最初の要素を変更
	if(p.current()->prev != nullptr) p.current()->prev->succ = p.current()->succ;
	if(p.current()->succ != nullptr) p.current()->succ->prev = p.current()->prev;
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
		erase(back_it());
}

// 最後の要素を返す（低速注意）
template<class Elem> Elem& list<Elem>::back(){
	Link<Elem>* p = first;
	for(p = first; p->succ != nullptr; ++p);
	return p->val; 	
}

// 最も大きな値を持つ[first:last)の範囲内の要素へのイテレータを返す
template<class Iterator> Iterator high(Iterator first, Iterator last){
	Iterator high = first;
	for(Iterator p = first; p != last; ++p)
		if(*high < *p) high = p;
	return high;
}

void f(){
	list<int> lst;
	int x;
	while(cin >> x && x) 	// 0で終了
		lst.push_front(x);

	list<int>::iterator p = high(lst.begin(), lst.end());
	cout << "the highest value was " << *p << endl;
}

int main(){
	f();

	// ここから挿入・削除のテスト
	int x;
	list<double> lst;

	while(cin >> x && x) 	// 0で終了
		lst.push_front(x);
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;

	while(cin >> x && x) 	// 0で終了
		lst.push_back(x);
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;

	lst.pop_front();		// 前から削除
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;

	lst.pop_back();			// 後から削除
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;
}