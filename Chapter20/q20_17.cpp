#include <iostream>
#include <vector>
using namespace std;

// ポインタを渡して追加したオブジェクトを所有（デストラクタでdelete）するvector
template<class T> class ownership_vector{
public:
	// デストラクタ
	~ownership_vector(){ 
		for(int i = 0; i < ptr.size(); ++i) 
			delete v[i]; 
	}

	// 基本的なメンバ関数のみ提供
	T& operator[](int pos) { return *v[pos]; }
	T& at(int pos) { return *v.at(pos); }

	T& operator*() { return *this; };

	typename vector<T*>::iterator begin() { return v.begin(); }
	typename vector<T*>::iterator end() { return v.end(); }

	void push_back(T* tp){ v.push_back(tp); ptr.push_back(tp); }
	void push_back(T& t){ v.push_back(&t); }

	void pop_back(){
		if(v.size() > 0){
			if(v[v.size() - 1] == ptr[ptr.size() - 1]){
				delete ptr[ptr.size() - 1];	// オブジェクトを削除
				ptr.pop_back();
			}
			v.pop_back();
		}
	}

	int size(){ return v.size(); }

private:
	vector<T*> v;
	vector<T*> ptr;	// ここに入っているポインタはこのクラスでdelete
};

int main(){
	ownership_vector<string> ovs;
	ovs.push_back(new string("Apple"));
	string s = "Banana";
	ovs.push_back(s);

	cout << ovs[0] << ' ' << ovs.at(1) << endl;

	ovs.pop_back();
	for(vector<string*>::iterator it = ovs.begin(); it != ovs.end(); ++it)
		cout << **it << endl;
}