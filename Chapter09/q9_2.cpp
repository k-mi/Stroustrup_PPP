#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Name_pair{
public:
	void read_names();	// 名前を入力
	void read_ages();	// 年齢を入力
	void print();		// 名前と年齢のペアを出力
	void sort();		// 名前をアルファベット順にソート 

private:
	vector<string> m_name;	// 名前
	vector<double> m_age;	// 年齢
};

// メンバ関数:
void Name_pair::read_names(){
	string tmp;
	cout << "名前 > ";
	while(cin >> tmp && tmp != "..."){	// macで動作しないため2つ目の条件を追加
		cout << "名前 > ";
		m_name.push_back(tmp);
	}

	// cinのバッファをflushする
	cin.clear();
	int StreamBufSize = cin.rdbuf()->in_avail();
	cin.ignore(StreamBufSize, EOF);
}

void Name_pair::read_ages(){
	int tmp;
	for(int i = 0; i < m_name.size(); ++i){
		cout << m_name[i] << " の年齢 > ";
		cin >> tmp;
		m_age.push_back(tmp);
	}
}

void Name_pair::print(){
	for(int i = 0; i < m_name.size(); ++i)
		cout << m_name[i] << '(' << m_age[i] << ')' << endl;
}

void Name_pair::sort(){
	vector<string> name = m_name;
	vector<double> age = m_age;

	std::sort(m_name.begin(), m_name.end());

	for(int i = 0; i < name.size(); ++i){
		for(int j = 0; j < m_name.size(); ++j){
			if(name[i] == m_name[j]){
				m_age[i] = age[j];
				break;
			}
		}
	}
}

int main(){
	Name_pair np;
	np.read_names();
	np.read_ages();
	np.print();
	np.sort();
	np.print();
}