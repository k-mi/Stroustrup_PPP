#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template<class T> ostream& operator<<(ostream& os, const vector<T>& v){
	if(!os) return os;
	for(int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	return os;
}

vector<double>* list_to_vector(const list<int>& l){
	vector<double>* v = new vector<double>;

	for(list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
		v->push_back(*it);

	return v;
}	

int main(){
	list<int> l(5, 5);
	l.push_back(1);
	l.push_back(3);
	l.push_back(2);
	l.push_front(99);

	vector<double>* v = list_to_vector(l);
	cout << *v << endl;	

	sort(v->begin(), v->end());	// ランダムアクセスイテレータでしか使用できない		
	cout << *v << endl;	

	delete v;
}