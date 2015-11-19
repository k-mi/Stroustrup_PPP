#include "Graph.h"

namespace Graph_lib{
	class Group : public Shape{
	public:
		Group() { }
		Group(Vector_ref<Shape>& vs);

		void add_shape(Shape& s){ shapes.push_back(s); }

		void draw() const;
		virtual void move(int dx, int dy);

		void set_color(Color col);		
		void set_style(Line_style sty);	// なぜか反映されない
		void set_fill_color(Color col);

		void draw_lines() const;		// Shapeクラスでもpublicに指定する必要あり

	private:
		Vector_ref<Shape> shapes;

		Shape::color;
		Shape::style;
		Shape::fill_color;
	
		Shape::point;
		Shape::number_of_points;

		Shape::add;
		Shape::set_point;
	};

	Group::Group(Vector_ref<Shape>& vs){
		for(int i = 0; i < vs.size(); ++i)
			shapes.push_back(vs[i]);
	}

	void Group::draw() const{	
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].draw();
	}

	void Group::move(int dx, int dy){
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].move(dx, dy);
	}

	void Group::set_color(Color col){
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].set_color(col);
	}

	void Group::set_style(Line_style sty){
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].set_style(sty);
	}

	void Group::set_fill_color(Color col){
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].set_fill_color(col);
	}

	void Group::draw_lines() const{
		for(int i = 0; i < shapes.size(); ++i)
			shapes[i].draw_lines();
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Group");

	const int a = 50;	// マス幅
	const int n = 8;	// 1行のマス数

	Vector_ref<Shape> vs1;
	Vector_ref<Shape> vs2;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if((i + j * n + j) % 2 == 0)
				vs1.push_back(new Graph_lib::Rectangle(Point(i * a, j * a), a, a));
			else
				vs2.push_back(new Graph_lib::Rectangle(Point(i * a, j * a), a, a));
		}
	}

	Group g1(vs1);
	Group g2(vs2);
	g1.set_fill_color(Color::white);
	g1.set_color(Color::invisible);
	g2.set_fill_color(Color::black);
	g2.set_color(Color::invisible);

	win.attach(g1);
	win.attach(g2);
	win.wait_for_button();
}