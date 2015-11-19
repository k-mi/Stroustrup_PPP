#include <iostream>
#include <stdexcept>
using namespace std;

class Patron{
public:
	Patron(string name, int id, int charge = 0) : m_name(name), m_id(id), m_charge(charge) { }

	string get_name() const { return m_name; }
	int get_id() const { return m_id; }
	int get_charge() const { return m_charge; }

	void set_charge(int n) {
		if(n < 0) runtime_error("invalid: charge");
		m_charge = n;
	} 

private:
	string m_name;	// 利用者の名前
	int m_id;		// 図書館カードの番号
	int m_charge;		// 利用料
};

// Patronのヘルパー関数: 利用料を支払う場合はtrue
bool is_charge(const Patron& p){
	return p.get_charge() == 0 ? false : true;
}

int main(){
	Patron p("Apple", 12345678);

	if(is_charge(p) == false){
		cout << "charge = 0" << endl;
		p.set_charge(100);
	}
}