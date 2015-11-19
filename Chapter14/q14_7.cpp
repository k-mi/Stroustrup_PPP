#include <cmath>
#include <stack>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);

	class Striped_closed_polyline : public Closed_polyline{
	public:
		Striped_closed_polyline() { }

		void draw_lines() const;
	};

	// ３つの点とストライプのy座標範囲より三角形にストライプを描画
	void triangle_stripe(Point p1, Point p2, Point p3, int start, int end){
		// 3つの点をy座標でソート（minがウインドウ内で一番上）
		Point min, mid, max;
		if(p1.y < p2.y && p1.y < p3.y){
			min = p1;
			mid = p2.y < p3.y ? p2 : p3;
			max = p2.y < p3.y ? p3 : p2;
		}
		else if(p2.y < p1.y && p2.y < p3.y){
			min = p2;
			mid = p1.y < p3.y ? p1 : p3;
			max = p1.y < p3.y ? p3 : p1;
		}
		else if(p3.y < p1.y && p3.y < p2.y){
			min = p3;
			mid = p1.y < p2.y ? p1 : p2;
			max = p1.y < p2.y ? p2 : p1;
		}

		int x1, x2;
		double max_min_a = max.y - min.y != 0 ? double(max.x - min.x) / (max.y - min.y) : 0;	// 傾きの逆数
		double min_mid_a = mid.y - min.y != 0 ? double(mid.x - min.x) / (mid.y - min.y) : 0;
		double mid_max_a = max.y - mid.y != 0 ? double(max.x - mid.x) / (max.y - mid.y) : 0;

		for(int y = start; y <= end; y += 3){	// 3ドット間隔で描画
			if(min.y <= y && y <= max.y){		// 三角形の範囲内のみを描画
				// min-maxのx座標を求める
				x1 = max_min_a * (y - min.y) + min.x;

				// min-midかmid-maxのx座標を求める
				if(y <= mid.y) x2 = min_mid_a * (y - min.y) + min.x;
				else x2 = mid_max_a * (y - mid.y) + mid.x;

				// 描画
				if(x1 <= x2) fl_line(x1, y, x2, y);
				else fl_line(x2, y, x1, y);
			}
		}
	}

	// x座標でソートするための型
	struct Index_x{
		Index_x(int ii, int xx) : index(ii), x(xx) { }

		int index;	// Shape::pointsのインデックス
		int x;		// x座標
	};
	bool operator>(Index_x& i1, Index_x& i2){
		return i1.x > i2.x;
	}
	bool operator<(Index_x& i1, Index_x& i2){
		return i1.x < i2.x;
	}

	// 2つのインデックスとTTLを持つ型
	struct Edge{
		Edge(int i1, int i2, int t) : first(i1), second(i2), ttl(t) { }

		int first;	// 1つ目のインデックス
		int second;	// 2つ目のインデックス
		int ttl;	// TTL（生存時間）
	};

	// 2つのインデックスを持つedgeを探す
	int edge_index(int i1, int i2, vector<Edge>& e){
		for(int i = 0; i < e.size(); ++i){
			if(e[i].ttl >= 1){	// TTLが残ってる辺のみを使う
				if((e[i].first == i1 && e[i].second == i2) || (e[i].first == i2 && e[i].second == i1)) return i; // インデックスを返す
			}
		}
		return -1;	// 存在しなければ-1を返す
	}

	// Polylineに対して塗りつぶしの代わりにストライプを提供するクラス
	// "単調な多角形"のみ対応
	void Striped_closed_polyline::draw_lines() const{
		// ストライプ
		if(fill_color().visibility() && number_of_points() >= 3) {
			fl_color(fill_color().as_int());			

			// x座標でソート
			vector<Index_x> vx;	// インデックスとx座標
			for(int i = 0; i < number_of_points(); ++i)
				vx.push_back(Index_x(i, point(i).x));
			sort(vx.begin(), vx.end());

			// y座標の最小、最大
			int y_min = point(0).y;
			int y_max = point(0).y;
			for(int i = 1; i < number_of_points(); ++i){
				if(point(i).y < y_min) y_min = point(i).y;
				if(point(i).y > y_max) y_max = point(i).y;
			}

			// 辺を格納
			vector<Edge> edge;	// 辺
			for(int i = 0; i < number_of_points() - 1; ++i)	// 多角形の辺のTTLは1
				edge.push_back(Edge(i, i + 1, 1));
			edge.push_back(Edge(number_of_points() - 1, 0, 1));

			// 多角形を三角形に分割
			stack<int> st;	// 飛ばした点のインデックス
			st.push(0);
			st.push(1);
			for(int i = 2; i < number_of_points(); ++i){
				while(st.size() > 1){
					int next = vx[i].index + 1 < number_of_points() ? vx[i].index + 1 : 0;		// iの隣の点
					int prev = vx[i].index - 1 >= 0 ? vx[i].index - 1 : number_of_points() - 1;	// iの隣の点

					if(vx[st.top()].index != next && vx[st.top()].index != prev){
						fl_line(point(vx[i].index).x, point(vx[i].index).y, point(vx[st.top()].index).x, point(vx[st.top()].index).y); // 分割線を描画
						edge.push_back(Edge(vx[i].index, vx[st.top()].index, 2));	// 辺に追加（分割線の辺のTTLは2）
						st.pop();
					}
					else if(i == number_of_points() - 1) st.pop();
					else break;
				}
				st.push(i);
			}

			// 斜線を描画
			for(int i = 0; i < edge.size(); ++i){
				if(edge[i].ttl >= 1){	// TTLが残ってる辺のみを使う
					edge[i].ttl--;

					for(int j = 0; j < number_of_points(); ++j){
						if(edge[i].first != j && edge[i].second != j){
							int index1 = edge_index(edge[i].first, j, edge);
							int index2 = edge_index(edge[i].second, j, edge);
							if(index1 != -1 && index2 != -1){
								edge[index1].ttl--;
								edge[index2].ttl--;

								triangle_stripe(point(edge[i].first), point(edge[i].second), point(j), y_min, y_max);
							}
						}
					}
				}
			}

			fl_color(color().as_int());    // reset color
		}

		// 輪郭線
		if(color().visibility()){
			Shape::draw_lines();
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Striped_closed_polyline");

	Striped_closed_polyline scp;
	scp.add(Point(250, 200));
	scp.add(Point(100, 50));
	scp.add(Point(200, 300));
	scp.add(Point(500, 300));
	scp.add(Point(450, 150));
	scp.add(Point(400, 100));
	scp.add(Point(300, 20));

	scp.set_color(Color::blue);
	scp.set_fill_color(Color::black);	// 水平線の色を指定
	scp.set_style(Line_style(Line_style::solid, 5));

	win.attach(scp);
	win.wait_for_button();
}