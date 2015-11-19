#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

class Iterator{
public:
	virtual double* next() = 0;
};

class Vector_iterator : public Iterator{
public:
	Vector_iterator(vector<double>& vd) : v(vd), index(0) { }

	double* next(){
		if(index < v.size()) return &v[index++];
		else return 0;
	}

private:
	int index;
	vector<double>& v;
};

class List_iterator : public Iterator{
public:
	List_iterator(list<double>& ld) : l(ld) { it = l.begin(); }

	double* next(){
		if(it != l.end()) return &*it++;
		else return 0;
	}

private:
	list<double>& l;
	list<double>::iterator it;
};

void print(Iterator& it){
	double* d = it.next();
	while(d != 0){
		cout << *d << endl;
		d = it.next();
	}
}

int main(){
	// テスト	
	vector<double> v(5, 3.14);
	list<double> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	print(Vector_iterator(v));
	print(List_iterator(l));

	return 0;
}