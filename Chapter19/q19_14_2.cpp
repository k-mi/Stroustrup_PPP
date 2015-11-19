// Hunt the Wunpus GUI version(q19_14-15)

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include "Graph.h"
#include "GUI.h"
using namespace std;
using namespace Graph_lib;

#define M_PI (acos(-1))

//#define DEBUG

// 部屋
struct Room{
	Room() : num(-1), adjacent1(-1), adjacent2(-1), adjacent3(-1) { }

	int num;		// 部屋番号（インデックスとは異なる）

	int adjacent1;	// 隣接する部屋のインデックス
	int adjacent2;
	int adjacent3;
};

// 各オブジェクトの操作
class Object{
public:
	// 作成時にランダムで決定
	explicit Object(vector<Room>& r) : rooms(r){
		for(int i = 0; i < 4; ++i){
			int r;
			do{
				r = rand() % rooms.size();
			} while(already_num.find(r) != already_num.end());
			already_num.insert(r);
			objects[i] = r;
		}	

		// already_numからplayerの値を削除
		already_num.erase(objects[0]);

#ifdef DEBUG
		// 各値を出力
		cout << "player: " << objects[0] << "(" << rooms[objects[0]].num << ")" << endl;
		cout << "Wumpus: " << objects[1] << "(" << rooms[objects[1]].num << ")" << endl;
		cout << "bat: " << objects[2] << "(" << rooms[objects[2]].num << ")" << endl;
		cout << "pit: " << objects[3] << "(" << rooms[objects[3]].num << ")" << endl;
#endif
	}

	int player_index() { return objects[0]; }
	int player_num() { return rooms[objects[0]].num; }

	bool is_wumpus() { return objects[1] == objects[0]; }
	bool is_bat() { return objects[2] == objects[0]; }
	bool is_pit() { return objects[3] == objects[0]; }
	bool nearby_wumpus() { return (objects[1] == rooms[objects[0]].adjacent1 || objects[1] == rooms[objects[0]].adjacent2 || objects[1] == rooms[objects[0]].adjacent3); }
	bool nearby_bat() { return (objects[2] == rooms[objects[0]].adjacent1 || objects[2] == rooms[objects[0]].adjacent2 || objects[2] == rooms[objects[0]].adjacent3); }
	bool nearby_pit() { return (objects[3] == rooms[objects[0]].adjacent1 || objects[3] == rooms[objects[0]].adjacent2 || objects[3] == rooms[objects[0]].adjacent3);  }

	// プレイヤーを部屋番号numに移動する
	// 移動に成功すればtrueを返す
	bool move_player(int num){
		int index = ntoi(num);	// 移動先のインデックス
		int p = objects[0];		// 現在のインデックス

		if(rooms[p].adjacent1 == index || rooms[p].adjacent2 == index || rooms[p].adjacent3 == index){
			objects[0] = index;	// 移動
			return true;
		}
		return false;	// 移動失敗
	}

	// 矢を放った後にwumpusがランダムに隣の部屋に移動する
	void move_wumpus(){
		int r;
		do{
			r = rand() % 3;	// 3つのトンネルから1つをランダムで決定
							// ただし、他オブジェクトと重複しない位置を選ぶ
			if(r == 0 && already_num.find(rooms[objects[1]].adjacent1) != already_num.end())
				continue;
			else if(r == 1 && already_num.find(rooms[objects[1]].adjacent2) != already_num.end())
				continue;
			else if(r == 2 && already_num.find(rooms[objects[1]].adjacent3) != already_num.end())
				continue;
			else
				break;
		} while(true);

		already_num.erase(objects[1]);
		already_num.insert(r);
		objects[1] = r;

#ifdef DEBUG
		cout << "wumpus move to: " << r << "(" << rooms[r].num << ")" << endl;
#endif
	}

	// プレイヤー位置にいるコウモリの
	// 次の位置をランダムに決定してプレイヤーとともに移動
	void move_bat(){
		int index = objects[0];	// プレイヤーのインデックス
		int bat_index = -1;		// コウモリのインデックス
		for(int i = 2; i <= 2; ++i)
			if(objects[i] == index)
				bat_index = i;
		assert(bat_index == 2);	// 今はコウモリ1体だけなので必ず2になる	

		int r;
		do{
			r = rand() % rooms.size();
		} while(already_num.find(r) != already_num.end());

		already_num.erase(objects[bat_index]);
		already_num.insert(r);
		objects[bat_index] = r;
		objects[0] = r;
	}

	// index1がindex2の隣かどうか
	bool is_adjacent(int index1, int index2){
		return (rooms[index1].adjacent1 == index2 || rooms[index1].adjacent2 == index2 || rooms[index1].adjacent3 == index2);
	}

	// num1、num2、num3の順でその部屋番号に矢を投げる
	// Wumpusに当たれば（wumpusがいる部屋を通れば）trueを返す
	bool shoot(int num1, int num2, int num3){
		int index1 = ntoi(num1);
		int index2 = ntoi(num2);
		int index3 = ntoi(num3);

		if(is_adjacent(objects[0], index1) && objects[1] == index1)
			return true;
		if(is_adjacent(objects[0], index1) && is_adjacent(index1, index2) && objects[1] == index2)
			return true;
		if(is_adjacent(objects[0], index1) && is_adjacent(index1, index2) && is_adjacent(index2, index3) && objects[1] == index3)
			return true;
		return false;
	}

	// 部屋番号からインデックスを求める
	int ntoi(int n){
		for(int i = 0; i < rooms.size(); ++i)
			if(rooms[i].num == n) return i;
		return -1;
	}

private:
	int objects[4];			// 各オブジェクトの位置（インデックス）
							// 0: player
							// 1: Wumpus
							// 2: 巨大コウモリ（bat）
							// 3: 底なし穴（pit）

	set<int> already_num;	// playerを除く何らかのオブジェクトが存在している位置（インデックス）
	vector<Room>& rooms;	// 部屋リストへの参照
};

// 洞窟を作成
vector<Room>& make(vector<Room>& rooms){
	// 2Dで表現できる"各頂点に対して3つの辺を持つ形"として、
	// 正十二面体を無理矢理開いたようなモデルの洞窟を作成する（したがってrooms.size()は常に20とする）
	// なお、これは原作通りの構造であると考えられる
	int i_min = 0, i_max = 5;			// 内側の5個の部屋 index = [i_min:i_max)
	for(int i = i_min; i < i_max; ++i){	
		rooms[i].adjacent1 = i - 1 >= i_min ? i - 1 : i_max - 1;
		rooms[i].adjacent2 = i + 1 < i_max? i + 1 : i_min;
		rooms[i].adjacent3 = i_max + rooms[i].adjacent2 * 2;
	}
	i_min = 5; i_max = 15;				// 中間の10個の部屋 index = [i_min:i_max)
	for(int i = i_min; i < i_max; ++i){
		rooms[i].adjacent1 = i - 1 >= i_min ? i - 1 : i_max - 1;
		rooms[i].adjacent2 = i + 1 < i_max ? i + 1 : i_min;
		rooms[i].adjacent3 = i % 2 == 0 ? rooms[i].adjacent2 / 2 + 13 : rooms[i].adjacent1 / 2 - 3;
	}
	i_min = 15; i_max = rooms.size();	// 外側の5個の部屋 index = [i_min:i_max)
	for(int i = i_min; i < i_max; ++i){
		rooms[i].adjacent1 = i - 1 >= i_min ? i - 1 : i_max - 1;
		rooms[i].adjacent2 = i + 1 < i_max ? i + 1 : i_min;
		rooms[i].adjacent3 = (rooms[i].adjacent1 - i_min) * 2 + 6;
	}

	// 部屋に[0:rooms.size())のランダムで一意な番号を割り当てる
	set<int> already_num;	// すでに出た番号を保持
	for(int i = 0; i < rooms.size(); ++i){
		int r;
		do{
			r = rand() % rooms.size();
		} while(already_num.find(r) != already_num.end());
		already_num.insert(r);
		rooms[i].num = r;
	}

#ifdef DEBUG
	// 部屋番号リストを出力
	for(int i = 0; i < rooms.size(); ++i){
		cout << i << "(" << rooms[i].num << "): " 
			 << rooms[i].adjacent1 << "(" << rooms[rooms[i].adjacent1].num << ") "
			 << rooms[i].adjacent2 << "(" << rooms[rooms[i].adjacent2].num << ") "
			 << rooms[i].adjacent3 << "(" << rooms[rooms[i].adjacent3].num << ") " << endl;
	}
#endif

	return rooms;
}

// 情報のテキストを作成
string info(vector<Room>& rooms, Object& object, int arrow){
	ostringstream oss;

	int num = object.player_num();
	oss << "You are in room " << num << ".  ";

	int index = object.player_index();
	vector<int> sort_tmp;
	sort_tmp.push_back(rooms[rooms[index].adjacent1].num);
	sort_tmp.push_back(rooms[rooms[index].adjacent2].num);
	sort_tmp.push_back(rooms[rooms[index].adjacent3].num);
	sort(sort_tmp.begin(), sort_tmp.end());
	oss << "Tunnels lead to ";
	for(int i = 0; i < sort_tmp.size(); ++i){
		if(i != sort_tmp.size() - 1) oss << sort_tmp[i] << ",";
		else oss << sort_tmp[i] << ".  ";
	}

	oss << "Left " << arrow << " arrows.";

	return oss.str();
}

// インデックスに対する座標を返す
Point coordinate(int x_max, int y_max, int index){
	double angle = 0;
	int radius = min(x_max, y_max) / 2;

	if(0 <= index && index < 5){		// 内側の5個の部屋
		angle = -2 * M_PI / 5 * index + M_PI / 2;
		radius *= 1 / 3.0;
	}
	else if(5 <= index && index < 15){	// 中間の10個の部屋
		angle = -2 * M_PI / 10 * (index - 5) + 162 * M_PI / 180;
		radius *= 2 / 3.0;
	}
	else if(15 <= index && index < 20){	// 外側5個の部屋
		angle = -2 * M_PI / 5 * (index - 15) - 162 * M_PI / 180;
	}
	
	return Point(x_max / 2 + radius * cos(angle), y_max / 2 + radius * -sin(angle));
}

// 文字の入った円のクラス
class Circle_text : public Circle{
public:
	Circle_text(Point p, int rr, const string& s) : Circle(p, rr), text(s) { }

	void draw_lines() const{
		Circle::draw_lines();
		Text t(Point(point(0).x + radius() / 2, point(0).y + radius() * 1.5), text);
		t.set_font_size(20);
		t.draw();
	}

private:
	string text;
};

// 色を更新
void update_color(Vector_ref<Shape>& circle, int player, int wumpus, int bat, int pit){
	for(int i = 0; i < circle.size(); ++i){
		// 上のほうが優先度が高い
		if(player == i){
			circle[i].set_fill_color(Color::yellow);
			continue;
		}
		else if(wumpus == i){
			circle[i].set_fill_color(Color::red);
			continue;
		}
		else if(bat == i){
			circle[i].set_fill_color(Color::blue);
			continue;
		}
		else if(pit == i){
			circle[i].set_fill_color(Color::dark_green);
			continue;
		}
		else{
			circle[i].set_fill_color(Color::white);
		}
	}
}

// GUIウインドウ
class Wunpus_window : public Graph_lib::Window{
public:
	Wunpus_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		rooms(20), object(make(rooms)), arrow(5), mark_wumpus(-1), mark_bat(-1), mark_pit(-1),	// ゲームの初期化
		text_info(Point(0, y_max() - 50), "Info"),
		text_prompt(Point(0, y_max() - 34), "Prompt"),
		text_wumpus(Point(0, y_max() - 66), "I smell a wumpus."),
		text_bat(Point(150, y_max() - 66), "Bat nearby."),
		text_pit(Point(250, y_max() - 66), "I feel a draft."),
		inbox(Point(0, y_max() - 30), x_max() - 80, 20, ""),
		enter_button(Point(x_max() - 70, y_max() - 30), 70, 20, "Enter", cb_enter),
		game_state(0)
	{
		attach(text_info);
		attach(text_prompt);
		attach(text_wumpus);
		attach(text_bat);
		attach(text_pit);
		attach(inbox);
		attach(enter_button);

		// 表示テキストのフォントを設定
		text_info.set_font(Font(Font::Font_type::helvetica_bold));
		text_info.set_font_size(16);
		text_prompt.set_font(Font(Font::Font_type::helvetica_bold));
		text_prompt.set_font_size(16);
		text_wumpus.set_font(Font(Font::Font_type::helvetica_bold));
		text_wumpus.set_font_size(16);
		text_bat.set_font(Font(Font::Font_type::helvetica_bold));
		text_bat.set_font_size(16);
		text_pit.set_font(Font(Font::Font_type::helvetica_bold));
		text_pit.set_font_size(16);

		// マップに関するオブジェクトを追加
		int index = object.player_index();

		attach(line);
		line.set_style(Line_style(Line_style::solid, 10));
		line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent1));
		line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent2));
		line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent3));

		for(int i = 0; i < 20; ++i){
			circle.push_back(new Circle_text(coordinate(x_max(), y_max() - 100, i), 20, to_string(rooms[i].num)));	// 最初に全ての部屋を作成し、必要に応じてattachする
			circle[circle.size() - 1].set_fill_color(Color::white);
		}
		attach(circle[index]);
		attach(circle[rooms[index].adjacent1]);
		attach(circle[rooms[index].adjacent2]);
		attach(circle[rooms[index].adjacent3]);
		circle[index].set_fill_color(Color::yellow);

		// プロンプトを表示
		text_prompt.set_label("Shoot or Move (S-M)?");

		// 警告を表示
		text_wumpus.set_color(object.nearby_wumpus() ? Color::red : Color(0xE0E0E0FF));
		text_bat.set_color(object.nearby_bat() ? Color::blue : Color(0xE0E0E0FF));
		text_pit.set_color(object.nearby_pit() ? Color::dark_green : Color(0xE0E0E0FF));

		// 情報を表示
		text_info.set_label(info(rooms, object, arrow));
	}

private:
	// ゲーム
	vector<Room> rooms;	// 部屋リスト
	Object object;		// 各オブジェクト
	int arrow;			// 矢の残数
	int mark_wumpus;	// マークしているWumpusのインデックス
	int mark_bat;		// マークしているコウモリのインデックス
	int mark_pit;		// マークしている底なし穴のインデックス

	// GUI(output)
	Text text_info;		// 情報（現在位置、隣接する部屋、矢の残数）
	Text text_prompt;	// プロンプト
	Text text_wumpus;	// Wumpusの警告文
	Text text_bat;		// コウモリの警告文
	Text text_pit;		// 底なし穴の警告文

	// GUI(input)
	In_box inbox;			// 入力ボックス
	Button enter_button;	// Enterボタン

	int game_state;			// ゲームの状態
							// 0: 次の操作: 入力待ち（ゲーム開始）
							// 1: 矢を射る: 入力待ち
							// 2: 移動: 入力待ち
							// 3-5: マーク: 入力待ち
							// -1: ゲーム終了: 次のゲームへ

	// GUI(map)
	Vector_ref<Shape> circle;	// 部屋を表す円
	Lines line;					// トンネルを表す線

	static void cb_enter(Address, Address pw) { reference_to<Wunpus_window>(pw).enter(); }

	void enter() {
		istringstream iss(inbox.get_string());	 // inboxからの入力
		ostringstream oss;						 // text_promptへの出力

		// 対処
		switch(game_state)
		{
			case 0:	// 次の操作: 入力待ち（ゲーム開始）
			{
				char action;
				iss >> action;
				if(!iss){
					oss << "Shoot or Move (S-M)?";
					return;
				}

				if(action == 'S' || action == 's'){
					game_state = 1;	// 矢を射る
					oss << "Number of rooms(a-b-c)?";
				}
				else if(action == 'M' || action == 'm'){
					game_state = 2;	// 移動
					oss << "Where to?";
				}
				else if(action == 'W' || action == 'w'){
					game_state = 3;	// マーク
					oss << "Where do you mark(0-19)?";
				}
				else if(action == 'B' || action == 'b'){
					game_state = 4;	// マーク
					oss << "Where do you mark(0-19)?";
				}
				else if(action == 'P' || action == 'p'){
					game_state = 5;	// マーク
					oss << "Where do you mark(0-19)?";
				}
				else if(action == 'Q' || action == 'q'){
					exit(EXIT_SUCCESS);	// 終了
				}
				else{
					oss << "Shoot or Move (S-M)?";
				}
				break;
			}
			case 1:	// 矢を射る: 入力待ち
			{
				char ch1, ch2;
				int i1, i2, i3;
				iss >> i1 >> ch1 >> i2 >> ch2 >> i3;
				if(!iss || ch1 != '-' || ch2 != '-'){
					oss << "Wrong fromat. Number of rooms(a-b-c)?";
					break;   // フォーマットが異なっている場合
				}

				--arrow;
				if(object.shoot(i1, i2, i3)){	// 成功
					// クリア処理
					oss << "You are win!: Aha! You got the Wounpus!";
					text_prompt.set_color(Color::magenta);
					game_state = -1;			// 終了
				}
				else{							// 失敗
					oss << "Missed...";

					object.move_wumpus();

					if(object.is_wumpus()){		// wumpus当たり判定
						// ゲームオーバー
						oss << "Gameover: Oops! Bumped a Wumpus!";
						text_prompt.set_color(Color::red);
						game_state = -1;		// 終了
					}
					else if(arrow == 0){		// 矢が無くなった
						// ゲームオーバー
						oss << "Gameover: Ouch! Arrow got you!";
						text_prompt.set_color(Color::red);
						game_state = -1;		// 終了
					}					
					else{
						oss << "Shoot or Move (S-M)?";
						game_state = 0;			// 次の操作を待ち
					}
				}
				break;
			}
			case 2:
			{
				int next = 0;
				iss >> next;

				if(!iss || !object.move_player(next)){	// 移動先が正しくない
					oss << "Not possible. Where to?";
					break;
				}

				// マップに追加
				int index = object.player_index();
				line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent1));
				line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent2));
				line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent3));
				attach(circle[index]);
				attach(circle[rooms[index].adjacent1]);
				attach(circle[rooms[index].adjacent2]);
				attach(circle[rooms[index].adjacent3]);

				if(!object.is_wumpus() && !object.is_pit() && object.is_bat()){		// コウモリ当たり判定
					oss << "ZAP--Super bad snatch! Elsewheresville for you!  ";
					object.move_bat();
					
					// マップに追加
					index = object.player_index();
					line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent1));
					line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent2));
					line.add(coordinate(x_max(), y_max() - 100, index), coordinate(x_max(), y_max() - 100, rooms[index].adjacent3));
					attach(circle[index]);
					attach(circle[rooms[index].adjacent1]);
					attach(circle[rooms[index].adjacent2]);
					attach(circle[rooms[index].adjacent3]);
				}

				if(object.is_wumpus()){		// wumpus当たり判定
					// ゲームオーバー
					oss << "Gameover: Oops! Bumped a Wumpus!";
					text_prompt.set_color(Color::red);
					game_state = -1;		// 終了
				}
				else if(object.is_pit()){	// 穴当たり判定
					// ゲームオーバー
					oss << "Gameover: Yyyyiiiieeee . . . Fail in a pit";
					text_prompt.set_color(Color::red);
					game_state = -1;		// 終了
				}
				else{
					oss << "Shoot or Move (S-M)?";
					game_state = 0;			// 次の操作を待つ
				}
				break;
			}
			case 3:
			case 4:
			case 5:
			{
				int mark = 0;
				iss >> mark;
				if(-1 > mark || mark >= rooms.size()){
					oss << "Not possible. Where do you mark(0-19)?";
					break;
				}

				switch(game_state)
				{
					case 3:
						mark_wumpus = mark == -1 ? -1 : object.ntoi(mark);
						break;
					case 4:
						mark_bat = mark == -1 ? -1 : object.ntoi(mark);;
						break;
					case 5:
						mark_pit = mark == -1 ? -1 : object.ntoi(mark);
						break;
				}
				oss << "Shoot or Move (S-M)?";
				game_state = 0;			// 次の操作を待つ
				break;
			}
			case -1:
				hide();
				break;
			default:
				exit(EXIT_SUCCESS);
				break;
		}

		// 表示情報の更新
		text_info.set_label(info(rooms, object, arrow));
		text_prompt.set_label(oss.str());
		text_wumpus.set_color(object.nearby_wumpus() ? Color::red : Color(0xE0E0E0FF));
		text_bat.set_color(object.nearby_bat() ? Color::blue : Color(0xE0E0E0FF));
		text_pit.set_color(object.nearby_pit() ? Color::dark_green : Color(0xE0E0E0FF));

		// 色を更新
		update_color(circle, object.player_index(), mark_wumpus, mark_bat, mark_pit);			
		for(int i = 0; i < circle.size(); ++i)
			put_on_top(circle[i]);	// 最前面へ

		// 再描画
		Fl::redraw();
	}
};

int main(){
	srand(time(NULL));

	while(true){
		Wunpus_window win(Point(100, 100), 600, 400, "Hunt the Wunpus");
		gui_main();
	}
}
