#include <iostream>
#include <vector>
using namespace std;

// オブジェクトへのポインタを含み、
// そのデストラクタが各オブジェクトをdeleteするvector
template<class T> class pvector{
public:
	// デストラクタ 全ての要素がポイントしているオブジェクトをdelete
	~pvector(){ for(int i = 0; i < v.size(); ++i) delete v[i]; }

	// 基本的なメンバ関数のみ提供
	T operator[](int pos) { return v[pos]; }
	T at(int pos) { return v.at(pos); }

	typename vector<T>::iterator begin() { return v.begin(); }
	typename vector<T>::iterator end() { return v.end(); }

	void push_back(T pointer){ v.push_back(pointer); }

	void pop_back(){
		if(v.size() > 0){
			delete v[v.size() - 1];	
			v.pop_back();
		}
	}

	int size(){ return v.size(); }

private:
	vector<T> v;
};

int main(){
	pvector<string*> pvs;	// テンプレート引数にポインタ型を指定
	pvs.push_back(new string("Apple"));
	pvs.push_back(new string("Banana"));

	cout << *pvs[0] << ' ' << *pvs.at(1) << endl;

	pvs.pop_back();

	for(vector<string*>::iterator it = pvs.begin(); it != pvs.end(); ++it)
		cout << **it << endl;
}