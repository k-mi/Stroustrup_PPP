#include <iostream>
#include <vector>
#include <memory>	// auto_ptr
using namespace std;

class Tracer{
public:
	explicit Tracer(const string& s) 
		: text(s) { cout << "construct: " << text << endl; }
	Tracer(const Tracer& t)
		 : text(t.text) { cout << "copy: " << text << endl; }
	~Tracer() { cout << "destruct: " << text << endl; }

	Tracer& operator=(const Tracer& t){
		cout << "assignment: " << text << " = " << t.text << endl;
		text = t.text;
		return *this;
	}

	string text;
};

ostream& operator<<(ostream& os, Tracer& t){
	if(!os) return os;
	os << t.text;
	return os;
}

std::vector<Tracer>* make_vec(){
	auto_ptr< vector<Tracer> > p(new vector<Tracer>);
	
	p->push_back(Tracer("p[0]"));
	(*p).push_back(Tracer("p[1]"));

	cout << p->at(0) << ' ' << p->at(1) << endl;

	return p.release();
}

std::vector<Tracer>* make_vec_exception(){
	auto_ptr< vector<Tracer> > p(new vector<Tracer>);
	
	p->push_back(Tracer("q[0]"));
	(*p).push_back(Tracer("q[1]"));

	cout << p->at(0) << ' ' << p->at(1) << endl;
	p->at(2);	// 領域外参照でexceptionを発生させる

	return p.release();
}

Tracer t1("grobal");

int main(){
	try{
		Tracer t2("local1");
		Tracer t3 = Tracer("local2");
		t2 = t1;	// t2のtextが"grobal"になる

		Tracer* t4 = new Tracer("freestore");
		delete t4;

		vector<Tracer>* p = make_vec();
		cout << p->at(0) << ' ' << p->at(1) << endl;
		vector<Tracer>* q = make_vec_exception();		// 例外を投げる
		cout << q->at(0) << ' ' << q->at(1) << endl;	// 実行しない
	}
	catch(std::exception& e)
	{
		cout << e.what() << endl;
	}
}