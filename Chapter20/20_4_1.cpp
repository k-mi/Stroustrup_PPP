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