#include "Graph.h"

namespace Graph_lib{
	// 2分木を描画するクラス
	class Binary_tree : public Shape{
	public:
		// levels: レベル数, h: レベルごとの高さ, r: 円の半径
		Binary_tree(Point p, int w, int levels, int h, int r);

		void draw_lines() const;

		void set_color(Color col);
		Color color() const { return lines.color(); }
		void set_style(Line_style sty);
		Line_style style() const { return lines.style(); }
		void set_fill_color(Color col);
		Color fill_color() const { return lines.fill_color(); }

	private:
		Vector_ref<Circle> v;
		Lines lines;

		Shape::move;
		Shape::set_point;
		Shape::add;
	};

	Binary_tree::Binary_tree(Point p, int w, int levels, int h = 100, int r = 20){
		if(w <= 0 || levels < 0 || h < r * 2 || r <= 0) error("Bad Binary_tree");
		add(p);

		double init = w - r * 2;			// レベルごとの最初のノードのx座標
		double space = 0, tmp_space = 0;	// ノード間の幅

		for(int i = 0; i <= levels; ++i){
			init /= 2;
			tmp_space = space;
			space = i == 0 ? 0 : (((w - r * 2) - init * 2) / (pow(2, i) - 1));

			for(int j = 0; j < pow(2, i); ++j){
				v.push_back(new Circle(Point(init + space * j + r + point(0).x, h * i + r + point(0).y), r));	// ノード（円）のオブジェクトを追加
				if(i > 0){
					lines.add(Point(init * 2 + tmp_space * (j / 2) + r + point(0).x, h * (i - 1) + r * 2 + point(0).y),
						Point(init + space * j + r + point(0).x, h * i + point(0).y));							// エッジ（線）のオブジェクトを追加
				}
			}
		}
	}

	void Binary_tree::draw_lines() const{
		for(int i = 0; i < v.size(); ++i)
			v[i].draw();
		lines.draw();
	}

	void Binary_tree::set_color(Color col){
		for(int i = 0; i < v.size(); ++i)
			v[i].set_color(col);
		lines.set_color(col);
	}
	void Binary_tree::set_style(Line_style sty){
		for(int i = 0; i < v.size(); ++i)
			v[i].set_style(sty);
		lines.set_style(sty);
	}
	void Binary_tree::set_fill_color(Color col){
		for(int i = 0; i < v.size(); ++i)
			v[i].set_fill_color(col);
		lines.set_fill_color(col);
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Binary_tree");

	Binary_tree bt(Point(0, 0), win.x_max(), 7, 50, 10);
	bt.set_fill_color(Color::dark_cyan);
	bt.set_style(Line_style(Line_style::solid, 2));

	win.attach(bt);
	win.wait_for_button();
}