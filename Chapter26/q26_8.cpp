#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>	// isspace, isdigit
#include <vector>
#include "Graph.h"
#include "Window.h"
using namespace Graph_lib;

class Text_interface {
public:
	Text_interface(string s) : text(s) { }

private:
	string text;
};

// 引数からオブジェクトへのポインタを返す関数
// 取得できなかった場合はnullptrを返す
// 注意: 受け取ったオブジェクトの解放を忘れずに
void* object_call(const string& code) {
	istringstream iss(code);
	
	string name = "";		// オブジェクト名
	char ch;
	while(iss.get(ch) && ch != '(') {
		if(isspace(ch)) return nullptr;
		name += ch;
	}
	if(!iss) return nullptr;
	cout << "object: " << name << endl;

	vector<int> args;		// 引数の値(int)を格納
	vector<string> objs;	// 入れ子のオブジェクト部分を格納

	int i_tmp;
	while(iss.get(ch)) {
		if(isdigit(ch)) {
			iss.unget();

			iss >> i_tmp;
			args.push_back(i_tmp);
			cout << "\targument: " << i_tmp << endl;
		}
		else if(isalpha(ch)) {
			iss.unget();

			string s_tmp = "";
			while(iss.get(ch) && ch != ')')	s_tmp += ch;
			s_tmp += ch;
			objs.push_back(s_tmp);
			cout << "\tnest_object: " << s_tmp << endl;
		}
		else continue;

		while(iss >> ch && ch != ')' && ch != ',');	// 次の閉じ括弧またはカンマまで飲み込む
		if(ch == ')') break;
		else if(!iss || ch != ',') return nullptr;
	}					

	// 各オブジェクト名で判別
	if(name == "Point") {
		if(args.size() != 2) return nullptr;
		return new Point(args[0], args[1]);
	}
	else if(name == "Line") {
		if(objs.size() != 2) return nullptr;
		return new Line(*static_cast<Point*>(object_call(objs[0])), *static_cast<Point*>(object_call(objs[1])));
	}
	else if(name == "Rectangle") {
		if(args.size() != 2 || objs.size() != 1) return nullptr;
		return new Graph_lib::Rectangle(*static_cast<Point*>(object_call(objs[0])), args[0], args[1]);
	}
	else if(name == "Circle") {
		if(args.size() != 1 || objs.size() != 1) return nullptr;
		return new Circle(*static_cast<Point*>(object_call(objs[0])), args[0]);
	}	
	else if(name == "Ellipse") {
		if(args.size() != 2 || objs.size() != 1) return nullptr;
		return new Graph_lib::Ellipse(*static_cast<Point*>(object_call(objs[0])), args[0], args[1]);
	}		
	else return nullptr;
}

int main() {
	// 入力ファイルの各行にテキストインターフェイスを1つずつ
	// （例）	Line(Point(100, 100), Point(200, 200))

	string filename;
	cout << "input filiname: ";
	cin >> filename;
	ifstream ifs(filename);
	if(!ifs) {
		cerr << "can't open file: " << filename << endl;
		return 1;
	}

	Vector_ref<Shape> vs;
	string line;
	int count = 1;
	while(getline(ifs, line)) {
		void* ptr = object_call(line);
		if(ptr == nullptr)	// 無効な行は無視
			cerr << "Syntax error: Line" << count << " -> " << line << endl;
		else vs.push_back(static_cast<Shape*>(ptr));
		count++;
	}

	// 描画
	Graph_lib::Window win(Point(100, 100), 600, 400, "GUI textbase interface");

	for(int i = 0; i < vs.size(); ++i)
		win.attach(vs[i]);

	gui_main();
}						 