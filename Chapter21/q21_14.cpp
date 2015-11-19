#include <iostream>
#include <fstream>
#include <string>		// rfind
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>		// make_pait
#include <algorithm>	// max_element, min_element
using namespace std;

template<class T1, class T2> struct Pred_second {
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2) { return p1.second < p2.second; }
};

template<class T1, class T2> struct Pred_first_size {
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2) { return p1.first.size() < p2.first.size(); }
};

// 単語の頻度
int wordcount(map<string, int>& words, const string& word) {
	return words[word];
}

// 頻度による単語リスト
int frequency(map<string, int>& words, vector<string>& v, int n) {
	typedef map<string, int>::const_iterator cit;

	if(n == -1) {		// 存在する中の最大文字数
		cit it = max_element(words.begin(), words.end(), Pred_second<string, int>());
		if(it == words.end()) return -1;
		n = it->second;
	}
	else if(n < -1) {	// 存在する中の最小文字数
		cit it = min_element(words.begin(), words.end(), Pred_second<string, int>());
		if(it == words.end()) return -1;
		n = it->second;
	}

	for(cit it = words.begin(); it != words.end(); ++it)
		if(it->second == n)
			v.push_back(it->first);

	return n;
}

// 長さによる単語リスト
int length(map<string, int>& words, unordered_map<string, int>& um, int n) {
	typedef map<string, int>::const_iterator cit;

	if(n == -1) {			// 存在する中の最も長い単語
		cit it = max_element(words.begin(), words.end(), Pred_first_size<string, int>());
		if(it == words.end()) return -1;
		n = it->first.size();
	}
	else if(n < -1) {	// 存在する中の最も短い単語
		cit it = min_element(words.begin(), words.end(), Pred_first_size<string, int>());
		if(it == words.end()) return -1;
		n = it->first.size();
	}

	for(cit it = words.begin(); it != words.end(); ++it)
		if(it->first.size() == n)
			um.insert(make_pair(it->first, it->second));

	return n;
}

// 前方一致検索による単語リスト
void f_search(map<string, int>& words, unordered_map<string, int>& um, string s) {
	typedef map<string, int>::const_iterator cit;

	for(cit it = words.begin(); it != words.end(); ++it) {
		if((s.length() <= 1 && it->first.rfind(s, s.length() - 1) != string::npos)
			|| (s.length() > 1 && it->first.rfind(s, s.length() - 2) != string::npos))
			um.insert(make_pair(it->first, it->second));
	}
}

int main() {
	string filename;	// ファイル名
	cout << "inputfile: ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) {
		cerr << "input file can't open: " << filename << endl;
		return 0;
	}

	string tmp;
	map<string, int> words;			// 単語を保持する
	while(ifs >> tmp) ++words[tmp];
	
	string func;
	while(cin >> func) {
		string arg;
	
		if(func == "quit") break;
		else if(func == "all") {
			for(map<string, int>::const_iterator it = words.begin(); it != words.end(); ++it)
				cout << it->first << ": " << it->second << endl;
		}
		else if(func == "count") {
			cin >> arg;
			cout << wordcount(words, arg) << endl;
		}
		else if(func == "freq") {
			cin >> arg;
			int n = atoi(arg.c_str());
			if(n < 0) {
				cout << "(nil)" << endl << endl;
				continue;
			}

			vector<string> list;
			if(arg == "max") cout << "frequency: " << frequency(words, list, -1) << endl;
			else if(arg == "min") cout << "frequency: " << frequency(words, list, -2) << endl;
			else frequency(words, list, n);

			if(list.size() == 0) cout << "(nil)" << endl;
			for(vector<string>::const_iterator it = list.begin(); it != list.end(); ++it)
				cout << *it << endl;
		}
		else if(func == "length") {
			cin >> arg;
			int n = atoi(arg.c_str());
			if(n < 0) {
				cout << "(nil)" << endl << endl;
				continue;
			}

			unordered_map<string, int> list;
			if(arg == "max") cout << "word: " << length(words, list, -1) << endl;
			else if(arg == "min") cout << "word: " << length(words, list, -2) << endl;
			else length(words, list, n);

			if(list.size() == 0) cout << "(nil)" << endl;
			for(unordered_map<string, int>::const_iterator it = list.begin(); it != list.end(); ++it)
				cout << it->first << ": " << it->second << endl;
		}
		else if(func == "find") {
			cin >> arg;
			unordered_map<string, int> list;

			f_search(words, list, arg);

			if(list.size() == 0) cout << "(nil)" << endl;
			for(unordered_map<string, int>::const_iterator it = list.begin(); it != list.end(); ++it)
				cout << it->first << ": " << it->second << endl;
		}
		else cout << "invalid command (can use: all, count, freq, length, find, quit)" << endl;

		cout << endl;
	}
}