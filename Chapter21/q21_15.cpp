#include <fstream>
#include <string>		// rfind
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>		// make_pait
#include <algorithm>	// max_element, min_element

#include "GUI.h"
#include "Graph.h"
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


namespace Graph_lib {
	class Search_window : public Graph_lib::Window {
	public:
		Search_window(Point xy, int w, int h, const string& title)
			: Window(xy, w, h, title),
			inbox_file(Point(70, 10), x_max() - 230, 30, "filename:"),
			inbox_search(Point(70, 40), x_max() - 230, 30, "target:"),
			button_count(Point(x_max() - 150, 10), 60, 30, "count", cb_count),
			button_freq(Point(x_max() - 80, 10), 60, 30, "freq", cb_freq),
			button_length(Point(x_max() - 150, 40), 60, 30, "length", cb_length),
			button_find(Point(x_max() - 80, 40), 60, 30, "find", cb_find),
			text_y(90), textlist(nullptr)
		{
			attach(inbox_file);
			attach(inbox_search);
			attach(button_count);
			attach(button_freq);
			attach(button_length);
			attach(button_find);
		}

	private:
		In_box inbox_file;
		In_box inbox_search;
		Button button_count;
		Button button_freq;
		Button button_length;
		Button button_find;

		Vector_ref<Text>* textlist;
		vector<string> list_v;
		int text_y;

		static void cb_count(Address, Address pw) { reference_to<Search_window>(pw).p_count(); }
		static void cb_freq(Address, Address pw) { reference_to<Search_window>(pw).p_freq(); }
		static void cb_length(Address, Address pw) { reference_to<Search_window>(pw).p_length(); }
		static void cb_find(Address, Address pw) { reference_to<Search_window>(pw).p_find(); }

		map<string, int> words;			// 単語を保持する

		// 初期化
		void init() {
			words.clear();
			string tmp;
			ifstream ifs(inbox_file.get_string().c_str());
			while(ifs >> tmp) ++words[tmp];

			list_v.clear();
			if(textlist != nullptr) {
				for(int i = 0; i < textlist->size(); ++i)
					detach((*textlist)[i]);
				delete textlist;
			}
			textlist = new Vector_ref<Text>;
		}

		void p_count() {
			init();

			string s = "Count == " + to_string(wordcount(words, inbox_search.get_string()));
			textlist->push_back(new Text(Point(10, text_y), s));

			attach((*textlist)[0]);
			Fl::redraw();	// 再描画
		}
		void p_freq() {
			init();

			int n = atoi(inbox_search.get_string().c_str());
			if(n < 0) {
				textlist->push_back(new Text(Point(10, text_y), "(nil)"));
				attach((*textlist)[0]);
				Fl::redraw();
				return;
			}

			string s = "frequency == ";
			vector<string> list;
			if(inbox_search.get_string() == "max") s += to_string(frequency(words, list, -1));
			else if(inbox_search.get_string() == "min") s += to_string(frequency(words, list, -2));
			else s += to_string(frequency(words, list, n));
			textlist->push_back(new Text(Point(10, text_y), s));

			int count = 1;
			if(list.size() == 0) textlist->push_back(new Text(Point(10, text_y + 20), "(nil)"));
			for(vector<string>::const_iterator it = list.begin(); it != list.end(); ++it) {
				textlist->push_back(new Text(Point(10, text_y + 20 * count), *it));
				++count;
			}

			for(int i = 0; i < textlist->size(); ++i)
				attach((*textlist)[i]);
			Fl::redraw();	// 再描画
		}
		void p_length() {
			init();

			int n = atoi(inbox_search.get_string().c_str());
			if(n < 0) {
				textlist->push_back(new Text(Point(10, text_y), "(nil)"));
				attach((*textlist)[0]);
				Fl::redraw();
				return;
			}

			string s = "word == ";
			unordered_map<string, int> list;
			if(inbox_search.get_string() == "max") s += to_string(length(words, list, -1));
			else if(inbox_search.get_string() == "min") s += to_string(length(words, list, -2));
			else s += to_string(length(words, list, n));
			textlist->push_back(new Text(Point(10, text_y), s));

			int count = 1;
			if(list.size() == 0) textlist->push_back(new Text(Point(10, text_y + 20), "(nil)"));
			for(unordered_map<string, int>::const_iterator it = list.begin(); it != list.end(); ++it) {
				textlist->push_back(new Text(Point(10, text_y + 20 * count), it->first + ": " + to_string(it->second)));
				++count;
			}

			for(int i = 0; i < textlist->size(); ++i)
				attach((*textlist)[i]);
			Fl::redraw();	// 再描画
		}
		void p_find() {
			init();

			unordered_map<string, int> list;

			f_search(words, list, inbox_search.get_string());
			textlist->push_back(new Text(Point(10, text_y), "find == " + to_string(list.size())));

			int count = 1;
			if(list.size() == 0) textlist->push_back(new Text(Point(10, text_y + 20), "(nil)"));
			for(unordered_map<string, int>::const_iterator it = list.begin(); it != list.end(); ++it) {
				textlist->push_back(new Text(Point(10, text_y + 20 * count), it->first + ": " + to_string(it->second)));
				++count;
			}

			for(int i = 0; i < textlist->size(); ++i)
				attach((*textlist)[i]);
			Fl::redraw();	// 再描画
		}
	};
}

int main() {
	using namespace Graph_lib;

	Search_window win(Point(100, 100), 600, 800, "Search word");
	gui_main();
}