#include <iostream>
#include <cmath>
#include <cstdlib>	// rand()
#include <ctime>	// time()
using namespace std;

// 最大レベルをmaxとした時、
// 0を返す確率が、1/2 + (1/2)^(Max+1)
// kを返す確率が、(1/2)^(k+1)の乱数発生器 
int skip_rand(int max){
	int r = rand() % int(pow(2, max + 1));

	int count = 0;	// カウント
	int x = max;	// レベル数
	int n = 1;		// 現在のレベルの個数（繰り返し数）
	while(x > 0){
		for(int i = 0; i < n; ++i){
			if(r == count) return x;
			count++;
		}		
		n *= 2;
		x -= 1;
	}

	return 0;	// 残りは0を返す
}

// スキップリスト
// 参考: http://d.hatena.ne.jp/kaiseh/20071231/1199122020 ほか
class Skip_lists{
public:
	char value;				// 値

	Skip_lists(int index, int value, int level, Skip_lists* next = nullptr, Skip_lists* lower = nullptr) 
		: m_index(index), value(value), m_level(level), m_next(next), m_lower(lower)
	{
		if(m_level > 0)
			m_lower = new Skip_lists(m_index, value, m_level - 1);
	}

	Skip_lists* add(Skip_lists* n);
	Skip_lists* find(int m_index);
	void print_all(int level) const;

private:
	int m_index;			// インデックス
	int m_level;			// このノードのレベル
	Skip_lists* m_next;		// 同じレベルの次のノード
	Skip_lists* m_lower;	// 下層へのノード
};

// インデックスが降順となるように、適切な位置にnを追加し、nを返す
Skip_lists* Skip_lists::add(Skip_lists* n){
	Skip_lists* p = this;
	Skip_lists* ret = n;

	while(p != nullptr){				// 最下層（m_level == 0）まで繰り返す
		if(p->m_level == n->m_level){	// nと同じレベルまでは何もしない
			Skip_lists* tmp = p;
			while(p != nullptr && p->m_index < n->m_index){
				tmp = p;
				p = p->m_next;
			}
			p = tmp;
			n->m_next = p->m_next;
			p->m_next = n;

			n = n->m_lower;
		}
		p = p->m_lower;
	}	

	return ret;
}

// 指定したインデックスのノードを返す
// 見つからなかった場合はnullptrを返す
Skip_lists* Skip_lists::find(int index){
	Skip_lists* p = this;
	int count = 0;			// 検索コスト

	while(p != nullptr){
		Skip_lists* tmp = p;
		while(p != nullptr && p->m_index <= index){
			// cout << p->m_level << ' ' << p->m_index << endl;	// 走査
			tmp = p;
			p = p->m_next;
			count++;
		}
		if(tmp->m_index == index){
			cout << "count: " << count << endl;
			return tmp;
		}
		p = tmp->m_lower;
	}	

	cout << "count: " << count << endl;
	return p;
}

// 引数で指定したレベルにある全てのインデックスを出力する
void Skip_lists::print_all(int level) const{
	const Skip_lists* p = this;
	while(p->m_level > level)
		p = p->m_lower;		

	cout << "Level" << level << ": ";
	while(p != nullptr){
		cout << p->m_index << ' ';
		p = p->m_next;
	}
	cout << endl;
}

int main(){
	srand(time(NULL));		// randのシード値を設定
	const int maxlevel = 6;	// Skip_listsで利用出来る最大のレベル

	Skip_lists* sl = new Skip_lists(0, '!', maxlevel);
	for(int i = 1; i < 64; ++i)
		sl->add(new Skip_lists(i, char(i + 32), skip_rand(maxlevel)));

	for(int i = maxlevel; i >= 0; --i)
		sl->print_all(i);

	int index;
	while(cin >> index){
		Skip_lists* f = sl->find(index);
		if(f != nullptr)
			cout << f->value << endl;
		else
			cout << "not found" << endl;		
	}
}