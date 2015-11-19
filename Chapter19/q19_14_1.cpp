// Hunt the Wunpus CUI(q18_12)
// 原作通りの構造の洞窟
// 部屋数は20で固定

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

// #define DEBUG

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
void make(vector<Room>& rooms){
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
		rooms[i].adjacent3 = (rooms[i].adjacent1 - i_min) * 2 + 1;
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
}

// ゲーム本体
// クリアなら0を、ゲームオーバーなら1を返す
int game(){
	vector<Room> rooms(20);	// 部屋リスト（部屋数は必ず20）
	make(rooms);			// 洞窟を作成
	Object object(rooms);	// オブジェクトを作成

	int arrow = 5;			// 矢の残数

	// メイン
	while(cin.good()){
		// 隣接時の警告表示
		if(object.nearby_wumpus()) cout << "I smell a wumpus（wumpusのにおいがする）" << endl;
		if(object.nearby_bat()) cout << "Bats nearby（コウモリの音が聞こえる）" << endl;
		if(object.nearby_pit()) cout << "I feel a draft（風が吹いている）" << endl;

		// 現在の部屋番号を表示
		int num = object.player_num();
		cout << "You are in room " << num << endl;

		// トンネルで接続されている部屋番号を表示
		int index = object.player_index();
		vector<int> tmp;
		tmp.push_back(rooms[rooms[index].adjacent1].num);
		tmp.push_back(rooms[rooms[index].adjacent2].num);
		tmp.push_back(rooms[rooms[index].adjacent3].num);
		sort(tmp.begin(), tmp.end());
		cout << "Tunnels lead to ";
		for(int i = 0; i < tmp.size(); ++i)
			cout << tmp[i] << ' ';
		cout << endl;	

		// 行動の入力
		char action;
		cout << "Shoot or Move (S-M)? ";
		while(cin >> action){	// 正しい入力が行われるまで繰り返す
			if(action == 'S' || action == 's'){	// 矢を射る
				char ch1, ch2;
				int i1, i2, i3;

				do{
					cout << "Number of rooms(a-b-c)? ";
					cin >> i1 >> ch1 >> i2 >> ch2 >> i3;

					if(ch1 != '-' || ch2 != '-'){
						cin.clear();
						cin.ignore();
					}
				} while(ch1 != '-' || ch2 != '-');	

				if(object.shoot(i1, i2, i3)){	// 成功
					// クリア処理
					cout << "Aha! You got the Wounpus!" << endl << endl;
					return 0;
				}
				else{							// 失敗
					cout << "Missed" << endl;
					--arrow;
					cout << arrow << " arrows left" << endl;

					object.move_wumpus();

					if(object.is_wumpus()){		// wumpus当たり判定
						// ゲームオーバー
						cout << "Oops! Bumped a Wumpus!" << endl << endl;
						return 1;
					}
					else if(arrow == 0){		// 矢が無くなった
						// ゲームオーバー
						cout << "Ouch! Arrow got you!" << endl << endl;
						return 1;
					}				
				}

				break;
			}
			else if(action == 'M' || action == 'm'){	// 移動する
				bool possible = false;
				int next = 0;

				do{
					cout << "Where to? ";
					cin >> next;
					possible = object.move_player(next);
					if(!possible){
						cout << "Not possible" << endl;	
						cin.clear();
						cin.ignore();	
					} 				
				}
				while(!possible);

				if(!object.is_wumpus() && !object.is_pit() && object.is_bat()){	// コウモリ当たり判定
					cout << "ZAP--Super bad snatch! Elsewheresville for you!" << endl << endl;
					object.move_bat();
				}	

				if(object.is_wumpus()){		// wumpus当たり判定
					// ゲームオーバー
					cout << "Oops! Bumped a Wumpus!" << endl << endl;
					return 1;
				}
				else if(object.is_pit()){	// 穴当たり判定
					// ゲームオーバー
					cout << "Yyyyiiiieeee . . . Fail in a pit" << endl << endl;
					return 1;
				}

				break;
			}
			else{
				cout << "Shoot or Move (S-M)? ";
				cin.clear();
				cin.ignore();	
			}	
		}
	}
	return -1;
}

int main(){
	srand(time(NULL));

	do{
		cout << "*** Hunt the Wumpus ***" << endl << endl;	// 開始時のメッセージ
		game();
	}
	while(cin.good());
}
