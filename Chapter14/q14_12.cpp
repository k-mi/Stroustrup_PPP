﻿#include "Graph.h"

namespace Graph_lib{
	// 2分木を描画するクラス
	class Binary_tree : public Shape{
	public:
		Binary_tree(Point xy, int w, int levels, int h, int r);

		virtual void draw_lines() const;

	protected:
		Point p;	// 描画する範囲の左上の座標
		int levels;	// レベル数
		int height;	// レベルごとの高さ
		int radius;	// 半径

	private:
		Shape::set_point;
		Shape::add;
	};

	class Binary_tree_rectangle : public Binary_tree{
	public:
		Binary_tree_rectangle(Point xy, int w, int levels, int h, int r) : Binary_tree(xy, w, levels, h, r){ }

		void draw_lines() const;
	};

	Binary_tree::Binary_tree(Point xy, int w, int l, int h = 100, int r = 20) : p(xy), levels(l), height(h), radius(r){
		if(w <= 0 || l < 0 || h < r * 2 || r <= 0) error("Bad Binary_tree");

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
		if(fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());

			for(int i = 0; i < number_of_points(); ++i)
				fl_pie(point(i).x, point(i).y, radius * 2 - 1, radius * 2 - 1, 0, 360);	// ノード（円）を描画

			fl_color(color().as_int());	// reset color
		}

		if(color().visibility()) {
			fl_color(color().as_int());

			int parent = 0;	// point(i)に対する親ノードのインデックス
			for(int i = 0; i < number_of_points(); ++i){
				fl_arc(point(i).x, point(i).y, radius * 2, radius * 2, 0, 360);			// ノード（円）を描画

				// エッジ（線）を描画
				if(i != 0){
					fl_line(point(parent).x + radius, point(parent).y + radius * 2, point(i).x + radius, point(i).y);
					if(i % 2 == 0) parent++;
				}
			}
		}
	}

	void Binary_tree_rectangle::draw_lines() const{
		if(fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());

			for(int i = 0; i < number_of_points(); ++i)
				fl_rectf(point(i).x, point(i).y, radius * 2, radius * 2);	// ノード（正方形）を描画

			fl_color(color().as_int());	// reset color
		}

		if(color().visibility()) {
			fl_color(color().as_int());

			int parent = 0;	// point(i)に対する親ノードのインデックス
			for(int i = 0; i < number_of_points(); ++i){
				fl_rect(point(i).x, point(i).y, radius * 2, radius * 2);	// ノード（正方形）を描画

				// エッジ（線）を描画
				if(i != 0){
					fl_line(point(parent).x + radius, point(parent).y + radius * 2, point(i).x + radius, point(i).y);
					if(i % 2 == 0) parent++;
				}
			}
		}
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 1280, 720, "Binary_tree2");

	Binary_tree bt(Point(50, 50), 800, 8, 50, 10);
	bt.set_fill_color(Color::dark_cyan);
	bt.set_style(Line_style(Line_style::solid, 2));

	Binary_tree_rectangle btr(Point(850, 300), 400, 3, 100, 20);
	btr.set_fill_color(Color::dark_magenta);
	btr.set_style(Line_style(Line_style::dot, 2));

	win.attach(bt);
	win.attach(btr);
	win.wait_for_button();
}