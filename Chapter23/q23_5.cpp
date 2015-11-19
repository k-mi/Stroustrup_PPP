#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>	// equal_range
#include <cstdlib> 		// exit
#include <regex>		// regex_match
#include <utility>		// make_pair
#include <ctime>		// clock
using namespace std;

typedef vector<string>::const_iterator Line_iter;

// Messageはメッセージの最初と最後の行をポイントする
class Message{
	Line_iter first;
	Line_iter last;	
public:
	Message(Line_iter p1, Line_iter p2) : first(p1), last(p2) { }
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
	//...
};

typedef vector<Message>::const_iterator Mess_iter;

// Mail_fileはファイルの行をすべて保持し、メッセージにアクセスしやすくする
struct Mail_file{
	string name;			// ファイル名
	vector<string> lines;	// 順番に並んだ行
	vector<Message> m;		// 順番に並んだメッセージ

	Mail_file(const string& n);	// ファイルnをlinesに読み込む

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

// "n"という名前のファイルを開く
// "n"の行を"lines"に読み込む
// linesでメッセージを検索し、それらをmにまとめる
// 便宜上、すべてのメッセージが"----"行で終わるものとする
Mail_file::Mail_file(const string& n){
	ifstream in(n.c_str());	// ファイルを開く
	if(!in){
		cerr << "no " << n << '\n';
		exit(1);
	}

	string s;
	while(getline(in, s)) lines.push_back(s);	// linesベクタを構築する

	Line_iter first = lines.begin();	// Messageのベクタを構築する
	for(Line_iter p = lines.begin(); p != lines.end(); ++p){
		if(*p == "----"){	// メッセージの終わり
			if(first != p)	// メッセージが存在する場合のみmに追加する
				m.push_back(Message(first, p));
			first = p + 1;	// ----はメッセージの一部ではない
		}
	}	
}

// MessageでSenderの名前を検索する
// 見つかった場合はtrueを返し、Senderの名前をsに変更する
bool find_from_addr(const Message* m, string& s){
	for(Line_iter p = m->begin(); p != m->end(); ++p){
		smatch matches;
		if(regex_match(*p, matches, regex("^From: (.+)"))){
			s = matches[1];
			return true;
		}
	}
	return false;
}

// MessageのSubjectを返すか、または""を返す
string find_subject(const Message* m){
	for(Line_iter p = m->begin(); p != m->end(); ++p){
		smatch matches;
		if(regex_match(*p, matches, regex("^Subject: (.+)"))) return matches[1];
	}
	return "";
}

int main(){
	string filename;
	cout << "input file: ";
	getline(cin, filename);
	Mail_file mfile(filename);	// mfileでファイルで初期化

	multimap<string, const Message*> m_sender;
	for(Mess_iter p = mfile.begin(); p != mfile.end(); ++p){
		const Message& m = *p;
		string s;
		if(find_from_addr(&m, s))
			m_sender.insert(make_pair(s, &m));
	}

	unordered_multimap<string, const Message*> um_sender;
	for(Mess_iter p = mfile.begin(); p != mfile.end(); ++p){
		const Message& m = *p;
		string s;
		if(find_from_addr(&m, s))
			um_sender.insert(make_pair(s, &m));
	}

	// 入力されたSenderを持つデータを検索する時間を計測
	clock_t t1, t2;	// 開始時刻、終了時刻

	string sender;	// 検索するSender
	cout << "search Sender: ";
	getline(cin, sender);	

	// multimapの計測
	t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	typedef multimap<string, const Message*>::const_iterator MCI;
	for(MCI p = m_sender.begin(); p != m_sender.end(); ++p)
		if(p->first == sender)
			find_subject(p->second);	// 表示はしない
		
	/* 順序づけを利用して、特定の部分のみを検索する場合
	pair<MCI, MCI> pp = m_sender.equal_range(sender);
	for(MCI p = pp.first; p != pp.second; ++p)
		find_subject(p->second);		// 表示はしない
	*/

	t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);
	cout << "ordered: " << double(t2 - t1) / CLOCKS_PER_SEC * 1000 << "[ms]" << endl;

	// unordered_multimapの計測
	t1 = clock();
	if(t1 == clock_t(-1)) exit(EXIT_FAILURE);

	typedef unordered_multimap<string, const Message*>::const_iterator UMCI;
	for(UMCI p = um_sender.begin(); p != um_sender.end(); ++p)
		if(p->first == sender)
			find_subject(p->second);	// 表示はしない

	t2 = clock();
	if(t2 == clock_t(-1)) exit(EXIT_FAILURE);
	cout << "unordered: " << double(t2 - t1) / CLOCKS_PER_SEC * 1000 << "[ms]" << endl;
}