#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	// 矢の種類
	enum Arrow_style{
		none,
		startpoint_arrow,
		endpoint_arrow,
	};

	// 矢印を描画するクラス
	class Arrow : public Shape{
	public:
		Arrow(Point p1, Point p2, Arrow_style as, int ll) : style(as), l(ll){
			add(p1);
			add(p2);
			if(l < 0) error("Bad arrow: negative arrow length");
		}

		void draw_lines() const;

	private:
		Arrow_style style;	// 矢の種類
		int l;				// 矢の長さ
	};

	// 2分木を描画するクラス
	class Binary_tree : public Shape{
	public:
		Binary_tree(Point xy, int w, int levels, int h, int r);

		virtual void draw_lines() const;
		
		// ノードにテキストを追加 
		// ルートから左、右、右、左、右下に移動する場合は第1引数に"lrrlr"を指定
		void add_text(const string& position, const string& text);
		void set_font(Font f) { fnt = f; }
		void set_font_size(int s) { fnt_sz = s; }

		void set_arrow_style(Arrow_style as) { style = as; }

	protected:
		Point p;			// 描画する範囲の左上の座標
		Arrow_style style;	// 矢印の種類

		int levels;			// レベル数
		int height;			// レベルごとの高さ
		int radius;			// 半径

		vector<string> vs;	// ノードのテキスト
		Font fnt;			// テキストのフォントの種類
		int fnt_sz;			// テキストのフォントサイズ

	private:
		Shape::set_point;
		Shape::add;
	};

	// ノードが正方形の2分木を描画するクラス
	class Binary_tree_rectangle : public Binary_tree{
	public:
		Binary_tree_rectangle(Point xy, int w, int levels, int h, int r) : Binary_tree(xy, w, levels, h, r){ }

		void draw_lines() const;
	};

	void Arrow::draw_lines() const{
		if(color().visibility()){
			double angle = atan2(point(1).x - point(0).x, -(point(1).y - point(0).y)) + M_PI / 2;
			fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
			switch(style)	// 矢の描画
			{
				case Arrow_style::startpoint_arrow:
					fl_line(point(0).x, point(0).y, point(0).x + l * cos(3 * M_PI / 4 + angle), point(0).y + l * sin(3 * M_PI / 4 + angle));
					fl_line(point(0).x, point(0).y, point(0).x + l * cos(5 * M_PI / 4 + angle), point(0).y + l * sin(5 * M_PI / 4 + angle));
					break;

				case Arrow_style::endpoint_arrow:
					fl_line(point(1).x, point(1).y, point(1).x + l * cos(M_PI / 4 + angle), point(1).y + l * sin(M_PI / 4 + angle));
					fl_line(point(1).x, point(1).y, point(1).x + l * cos(7 * M_PI / 4 + angle), point(1).y + l * sin(7 * M_PI / 4 + angle));
					break;
			}
		}
	}

	Binary_tree::Binary_tree(Point xy, int w, int l, int h = 100, int r = 20) 
		: p(xy), levels(l), height(h), radius(r), fnt(fl_font()), fnt_sz(fl_size()){

		if(w <= 0 || l < 0 || h < r * 2 || r <= 0) error("Bad Binary_tree");
		style = Arrow_style::none;
		vs.resize(pow(2, levels + 1), "");

		double init = w - r * 2;			// レベルごとの最初のノードのx座標
		double space = 0, tmp_space = 0;	// ノード間の幅

		for(int i = 0; i <= levels; ++i){
			init /= 2;
			tmp_space = space;
			space = i == 0 ? 0 : (((w - r * 2) - init * 2) / (pow(2, i) - 1));

			for(int j = 0; j < pow(2, i); ++j)
				Shape::add(Point(init + space * j + p.x, h * i + p.y));	// 各ノードの右上座標
		}
	}

	void Binary_tree::draw_lines() const{
		if(fill_color().visibility()) {
			for(int i = 0; i < number_of_points(); ++i){
				fl_color(fill_color().as_int());
				fl_pie(point(i).x, point(i).y, radius * 2 - 1, radius * 2 - 1, 0, 360);	// ノード（円）を描画

				fl_color(color().as_int());	// reset color
				Text t(Point(point(i).x, point(i).y + radius * 1.5), vs[i]);			// ノード（テキスト）を描画
				t.set_font(fnt);
				t.set_font_size(fnt_sz);
				t.draw_lines();
			}		
		}

		if(color().visibility()) {
			fl_color(color().as_int());

			int parent = 0;	// point(i)に対する親ノードのインデックス
			for(int i = 0; i < number_of_points(); ++i){
				fl_arc(point(i).x, point(i).y, radius * 2, radius * 2, 0, 360);	// ノード（円）を描画

				// エッジ（線）を描画
				if(i != 0){
					Arrow(Point(point(parent).x + radius, point(parent).y + radius * 2), Point(point(i).x + radius, point(i).y), style, radius / 2).draw_lines();
					if(i % 2 == 0) parent++;
				}
			}
		}
	}

	void Binary_tree::add_text(const string& position, const string& text){
		int index = 0;
		for(int i = 0; i < position.size(); ++i){
			if(position[i] == 'l') index = index * 2 + 1;		// 左下に移動
			else if(position[i] == 'r') index = index * 2 + 2;	// 右下に移動
			else error("Bad add_text");
		}

		if(index < vs.size()) vs[index] = text;
	}

	void Binary_tree_rectangle::draw_lines() const{
		if(fill_color().visibility()) {
			for(int i = 0; i < number_of_points(); ++i){
				fl_color(fill_color().as_int());
				fl_rectf(point(i).x, point(i).y, radius * 2, radius * 2);		// ノード（正方形）を描画

				fl_color(color().as_int());	// reset color
				Text t(Point(point(i).x, point(i).y + radius * 1.5), vs[i]);	// ノード（テキスト）を描画
				t.set_font(fnt);
				t.set_font_size(fnt_sz);
				t.draw_lines();
			}	
		}

		if(color().visibility()) {
			fl_color(color().as_int());

			int parent = 0;	// point(i)に対する親ノードのインデックス
			for(int i = 0; i < number_of_points(); ++i){
				fl_rect(point(i).x, point(i).y, radius * 2, radius * 2);	// ノード（正方形）を描画

				// エッジ（線）を描画
				if(i != 0){
					Arrow(Point(point(parent).x + radius, point(parent).y + radius * 2), Point(point(i).x + radius, point(i).y), style, radius / 2).draw_lines();
					if(i % 2 == 0) parent++;
				}
			}
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 1280, 720, "Binary_tree4");

	Binary_tree bt(Point(50, 50), 800, 8, 50, 10);
	bt.set_fill_color(Color::yellow);
	bt.set_style(Line_style(Line_style::solid, 2));
	bt.set_arrow_style(Arrow_style::endpoint_arrow);
	bt.set_font_size(12);
	bt.add_text("lrrlr", " 44");

	Binary_tree_rectangle btr(Point(850, 200), 400, 3, 100, 20);
	btr.set_fill_color(Color::magenta);
	btr.set_color(Color::dark_magenta);
	btr.set_style(Line_style(Line_style::dot, 5));
	btr.set_font_size(30);
	btr.add_text("", " 0");
	btr.add_text("l", " 1");
	btr.add_text("r", " 2");
	btr.move(0, 100);

	win.attach(bt);
	win.attach(btr);
	win.wait_for_button();
}