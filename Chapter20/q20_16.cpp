#include <iostream>
#include <vector>
using namespace std;

// []演算子と*演算子がポインタではなく、
// 要素によってポイントされるオブジェクトへの参照を返すpvector(q20_15)
template<class T> class ovector{
public:
	// デストラクタ 全ての要素がポイントしているオブジェクトをdelete
	~ovector(){ for(int i = 0; i < v.size(); ++i) delete v[i]; }

	// 基本的なメンバ関数のみ提供
	T& operator[](int pos) { return *v[pos]; }
	T& at(int pos) { return *v.at(pos); }

	T& operator*() { return *this; };

	typename vector<T*>::iterator begin() { return v.begin(); }
	typename vector<T*>::iterator end() { return v.end(); }

	void push_back(T* pointer){ v.push_back(pointer); }

	void pop_back(){
		if(v.size() > 0){
			delete v[v.size() - 1];	
			v.pop_back();
		}
	}

	int size(){ return v.size(); }

private:
	vector<T*> v;
};

int main(){
	ovector<string> ovs;	// 変更
	ovs.push_back(new string("Apple"));
	ovs.push_back(new string("Banana"));

	cout << ovs[0] << ' ' << ovs.at(1) << endl;

	ovs.pop_back();

	for(vector<string*>::iterator it = ovs.begin(); it != ovs.end(); ++it)
		cout << **it << endl;
}