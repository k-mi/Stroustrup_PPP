#include <cmath>
#include "Graph.h"

#define M_PI (acos(-1))

namespace Graph_lib{
	class Smiley : public Circle{	// 笑顔
	public:
		Smiley(Point p, int rr) : Circle(p, rr) { }	// 基底クラスの引数付きコンストラクタを呼ぶ

		void draw_lines() const;
	};

	class Frowny : public Circle{	// しかめ面
	public:
		Frowny(Point p, int rr) : Circle(p, rr) { }	// 基底クラスの引数付きコンストラクタを呼ぶ

		void draw_lines() const;
	};

	class Smiley_Hat : public Smiley{	// 帽子付き笑顔
	public:
		Smiley_Hat(Point p, int rr) : Smiley(p, rr) { }

		void draw_lines() const{
			Smiley::draw_lines();

			fl_line(center().x + radius() * cos(M_PI / 3), center().y - radius() * sin(M_PI / 3), 
				center().x, center().y - radius() * 2,
				center().x + radius() * cos(2 * M_PI / 3), center().y - radius() * sin(2 * M_PI / 3));
		}
	};

	class Frowny_Hat : public Frowny{	// 帽子付きしかめ面
	public:
		Frowny_Hat(Point p, int rr) : Frowny(p, rr) { }

		void draw_lines() const{
			Frowny::draw_lines();

			fl_line(center().x + radius() * cos(M_PI / 3), center().y - radius() * sin(M_PI / 3),
				center().x, center().y - radius() * 2,
				center().x + radius() * cos(2 * M_PI / 3), center().y - radius() * sin(2 * M_PI / 3));
		}
	};

	void Smiley::draw_lines() const
	{
		Circle::draw_lines();	// 円の部分はCircleと同じ
		
		if(color().visibility()) {
			fl_color(color().as_int());
			fl_arc(center().x + radius() / 2 * cos(M_PI / 4) - radius() / 16,
				center().y - radius() / 2 * sin(M_PI / 4) + radius() / 8, radius() / 8, radius() / 4, 0, 360);		// 右目
			fl_arc(center().x + radius() / 2 * cos(3 * M_PI / 4) - radius() / 16,
				center().y - radius() / 2 * sin(3 * M_PI / 4) + radius() / 8, radius() / 8, radius() / 4, 0, 360);	// 左目
			fl_arc(center().x - radius() / 2, center().y - radius() / 2, radius(), radius(), 225, 315);				// 口
		}
	}

	void Frowny::draw_lines() const
	{
		Circle::draw_lines();	// 円の部分はCircleと同じ

		if(color().visibility()) {
			fl_color(color().as_int());
			fl_arc(center().x + radius() / 2 * cos(M_PI / 4) - radius() / 16,
				center().y - radius() / 2 * sin(M_PI / 4) + radius() / 8, radius() / 8, radius() / 4, 0, 360);		// 右目
			fl_arc(center().x + radius() / 2 * cos(3 * M_PI / 4) - radius() / 16,
				center().y - radius() / 2 * sin(3 * M_PI / 4) + radius() / 8, radius() / 8, radius() / 4, 0, 360);	// 左目
			fl_arc(center().x - radius() / 2, center().y + radius() / 2, radius(), radius(), 45, 135);				// 口
		}
	}
}

#include "Simple_window.h"
int main(){
	Simple_window win(Point(100, 100), 600, 400, "Face");

	Smiley_Hat f1(Point(150, 200), 80);
	f1.set_fill_color(Color::magenta);
	f1.set_style(Line_style(Line_style::solid, 5));

	Frowny_Hat f2(Point(400, 200), 80);
	f2.set_fill_color(Color::red);
	f2.set_style(Line_style(Line_style::solid, 5));

	win.attach(f1);
	win.attach(f2);
	win.wait_for_button();
}