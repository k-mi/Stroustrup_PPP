#include "Graph.h"
#include <limits>

namespace Graph_lib{
	struct Data{
		Data(double d, string l, Color c) : data(d), label(l), color(c) {
			if(data <= 0) error("Bad data");
		}

		double data;	// データ
		string label;	// ラベル
		Color color;	// 色
	};

	class Bar_chart : public Shape{
	public:
		Bar_chart(Point xy, int w, int h);	// 棒グラフの左上の座標, 幅、高さ
		void draw_lines() const;

		void add_data(double data, string label, Color color);	// m_dataにデータを追加

		double max() { return m_max; }
		double min() { return m_min; }
		Data data(int i) { if(i < m_data.size()) return m_data[i]; }
		int number_of_data() { return m_data.size(); }

	protected:
		Shape::set_color;
		Shape::color;
		Shape::set_style;
		Shape::style;
		Shape::set_fill_color;
		Shape::fill_color;

	private:
		vector<Data> m_data;	// 基本データ
		double m_max;			// データの最大値
		double m_min;			// データの最小値

		int m_width;			// 棒グラフの幅
		int m_height;			// 棒グラフの高さ
	};

	Bar_chart::Bar_chart(Point xy, int w, int h) : m_width(w), m_height(h), m_max(0), m_min(numeric_limits<double>::max()){
		if(m_width <= 0 || m_height <= 0) error("Bad Bar_chart");
		add(xy);
	}

	void Bar_chart::draw_lines() const{
		if(m_data.size() == 0 || m_max == 0) return;

		const int xoffset = 40;											// ウインドウの左端からy軸までの距離
		const int yoffset = 40;											// ウインドウの右端からx軸までの距離
		const int space = 40;											// グラフの向こう側の領域

		const int xlength = m_width - xoffset - space;					// 軸の長さ
		const int ylength = m_height - yoffset - space;
		const int x_orig = xoffset;										// 原点
		const int y_orig = space + ylength;
		const Point orig(x_orig, y_orig);

		const double yscale = (double)ylength / m_max;					// y軸の倍率
		const int data_w = (xlength - space) / (m_data.size() * 2 - 1);	// 棒の幅

		// xy軸を描画
		Axis(Axis::x, Point(point(0).x + space, point(0).y + y_orig), xlength).draw_lines();
		Axis(Axis::y, Point(point(0).x + x_orig, point(0).y + ylength + space), ylength, 10, "one notch = " + to_string(m_max / 10)).draw_lines();

		// グラフの長方形・ラベルを作成、描画
		for(int i = 0; i < m_data.size(); ++i){
			Rectangle r(Point(point(0).x + space + space + data_w * i * 2, point(0).y + space + ylength - m_data[i].data * yscale + 1), data_w, m_data[i].data * yscale);
			r.set_fill_color(m_data[i].color);
			r.draw_lines();

			Text t(Point(r.point(0).x, r.point(0).y + m_data[i].data * yscale + 15), m_data[i].label);
			t.set_color(m_data[i].color);
			t.draw();
		}
	}

	void Bar_chart::add_data(double data, string label = "", Color color = Color::black){
		if(data > m_max) m_max = data;
		if(data < m_min) m_min = data;
		
		Data tmp(data, label, color);
		m_data.push_back(tmp);
	}
}

#include "Simple_window.h"

int main(){
	Simple_window win(Point(100, 100), 600, 400, "Bar_chart");

	Bar_chart bc1(Point(0, 0), win.x_max() / 2, win.y_max() / 2);
	bc1.add_data(100);
	bc1.add_data(600);
	bc1.add_data(300);
	bc1.add_data(700);
	bc1.add_data(200);

	Bar_chart bc2(Point(win.x_max() / 2, win.y_max() / 2), win.x_max() / 2, win.y_max() / 2);
	bc2.add_data(30, "7", Color::yellow);
	bc2.add_data(180, "1", Color::red);
	bc2.add_data(20, "8", Color::blue);
	bc2.add_data(150, "2", Color::yellow);
	bc2.add_data(70, "5", Color::yellow);
	bc2.add_data(40, "6", Color::yellow);
	bc2.add_data(130, "3", Color::yellow);
	bc2.add_data(90, "4", Color::yellow);

	win.attach(bc1);
	win.attach(bc2);
	win.wait_for_button();
}