#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Table{
	Table(string a, string b, string c, string d) :
		familyname(a), firstname(b), phonenumber(c), mailaddress(d){}

	string familyname;
	string firstname;
	string phonenumber;
	string mailaddress;
};

int main(){
	vector<Table> table;
	table.push_back(Table("Sano", "Kenjiro" , "09012345678", "fire_emblem@outlook.com"));
	table.push_back(Table("Samuragochi", "Mamoru" , "0425678901", "ghost_writer@gmail.com"));
	table.push_back(Table("Obokata", "Haruko" , "05098765432", "stap@docomo.ne.jp"));
	table.push_back(Table("Nonomura", "Ryutaro" , "08079797979", "bitter_cry@ezweb.ne.jp"));
	table.push_back(Table("Katayama", "Yusuke" , "07001010010", "remote@softbank.ne.jp"));

	for(int i = 0; i < table.size(); ++i){
		cout << setw(12) << table[i].familyname << '|'
			 << setw(12) << table[i].firstname << '|'
			 << setw(12) << table[i].phonenumber << '|'
			 << setw(24) << table[i].mailaddress << endl;
	}
}