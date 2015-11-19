#include "Graph.h"
#include <limits>

namespace Graph_lib{
	class Bar_chart : public Shape{
	public:
		Bar_chart(Point xy, int w, int h);	// 棒グラフの左上の座標, 幅、高さ
		void draw_lines() const;

		void add_data(double d);	// m_dataにデータを追加

		int max() { return m_max; }
		int min() { return m_min; }
		int data(int i) { if(i < m_data.size()) return m_data[i]; }
		int number_of_data() { return m_data.size(); }

	protected:
		Shape::set_color;
		Shape::color;
		Shape::set_style;
		Shape::style;
		Shape::set_fill_color;
		Shape::fill_color;

	private:
		vector<double> m_data;	// 基本データ
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

		const int xoffset = m_width / 10;								// ウインドウの左端からy軸までの距離
		const int yoffset = m_width / 10;								// ウインドウの右端からx軸までの距離
		const int space = m_width / 10;									// グラフの向こう側の領域

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

		// グラフの長方形を作成、描画
		for(int i = 0; i < m_data.size(); ++i){
			Rectangle r(Point(point(0).x + space + space + data_w * i * 2, point(0).y + space + ylength - m_data[i] * yscale + 1), data_w, m_data[i] * yscale);
			r.set_fill_color(Color::dark_cyan);
			r.draw_lines();
		}
			
	}

	void Bar_chart::add_data(double d){
		if(d <= 0) error("Bad data");
		if(d > m_max) m_max = d;
		if(d < m_min) m_min = d;
		m_data.push_back(d);
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
	bc2.add_data(30);
	bc2.add_data(180);
	bc2.add_data(20);
	bc2.add_data(150);
	bc2.add_data(70);
	bc2.add_data(40);
	bc2.add_data(130);
	bc2.add_data(90);

	win.attach(bc1);
	win.attach(bc2);
	win.wait_for_button();
}