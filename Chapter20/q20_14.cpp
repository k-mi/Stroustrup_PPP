#include <iostream>
using namespace std;

// 単方向リンクリスト
// push_back()、pop_back()、erase()はバックポインタを持たない関係で削除	
template<class Elem> struct Link{
	Link(const Elem& v = Elem(), Link* s = nullptr)
		: val(v), succ(s) { }

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

	iterator insert(iterator p, const Elem& v);	// リストのpの後（1つ後の要素）にvを挿入する

	void push_front(const Elem& v);	// vを最初に挿入する
	void pop_front();				// 最初の要素を削除する

	Elem& front() { return first->val; }	// 最初の要素

private:
	Link<Elem>* first;
};

template<class Elem> class list<Elem>::iterator{
public:
	iterator(Link<Elem>* p) : curr(p) { }

	// end()はヌルポインタであるため演算子使用不可
	iterator& operator++() { curr = curr->succ; return *this; }	// 前方
	Elem& operator*() { return curr->val; }		// 値を取得する（間接参照）

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }

	Link<Elem>* current() { return curr; }

private:
	Link<Elem>* curr;	// 現在のリンク
};

// リストのpの後（1つ"後"の要素）にvを挿入する
template<class Elem> typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v){
	if(p == end()) return p;
	p.current()->succ = new Link<Elem>(v, p.current()->succ);
	return ++p;
}

// vを最初（begin()の1つ前）に挿入する
template<class Elem> void list<Elem>::push_front(const Elem& v){
	first = new Link<Elem>(v, first);
}	

// 最初の要素（begin()）を削除する
template<class Elem> void list<Elem>::pop_front(){
	if(begin() != end()){	// 要素がある場合のみ実行
		Link<Elem>* tmp = first;
		first = first->succ;
		delete tmp;
	}	
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
		lst.push_front(x);	// 先頭に追加
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;

	lst.pop_front();		// 先頭から削除
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;

	while(cin >> x && x) 	// 0で終了
		lst.insert(lst.begin(), x);	// 先頭の次に追加（存在しない場合は何もしない）
	for(list<double>::iterator it = lst.begin(); it != lst.end(); ++it)	// 全要素を出力
		cout << *it << ' ';
	cout << endl;
}