#include "Graph.h"
#include <limits>

namespace Graph_lib{
	struct Data{
		Data(double d, string l, Color c) : data(d), label(l), color(c) { }

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

	Bar_chart::Bar_chart(Point xy, int w, int h) : m_width(w), m_height(h), m_max(numeric_limits<double>::min()), m_min(numeric_limits<double>::max()){
		if(m_width <= 0 || m_height <= 0) error("Bad Bar_chart");
		add(xy);
	}

	void Bar_chart::draw_lines() const{
		if(m_data.size() == 0) return;

		const int xoffset = 40;											// ウインドウの左端からy軸までの距離
		const int yoffset = 40;											// ウインドウの右端からx軸までの距離
		const int space = 40;											// グラフの向こう側の領域

		const int xlength = m_width - xoffset - space;					// 軸の長さ
		const int ylength = m_height - yoffset - space;

		const double yscale = (double)ylength / (m_max - m_min);		// y軸の倍率
		const int data_w = (xlength - space) / (m_data.size() * 2 - 1);	// 棒の幅

		const int x_orig = xoffset;										// 原点
		const int y_orig = space + ylength * ((double)m_max / ylength * yscale);
		const Point orig(x_orig, y_orig);

		// xy軸を描画
		Axis(Axis::x, Point(point(0).x + space, point(0).y + y_orig), xlength).draw_lines();
		Axis(Axis::y, Point(point(0).x + x_orig, point(0).y + ylength + space), ylength, 10, "one notch = " + to_string(m_max / 10)).draw_lines();

		// グラフの長方形・ラベルを作成、描画
		for(int i = 0; i < m_data.size(); ++i){
			int rx = point(0).x + space + space + data_w * i * 2;
			int ry = m_data[i].data < 0 ? (point(0).y + y_orig) : (point(0).y + y_orig - m_data[i].data * yscale);

			if(m_data[i].data != 0){	// 0の場合は描画しない
				Rectangle r(Point(rx, ry), data_w, abs(m_data[i].data) * yscale);
				r.set_fill_color(m_data[i].color);
				r.draw_lines();
			}

			int label_offset = m_data[i].data < 0 ? 0 : 15;
			Text t(Point(rx, ry + m_data[i].data * yscale + label_offset), m_data[i].label);
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
	Simple_window win(Point(100, 100), 600, 400, "Temperature");

	Bar_chart bc(Point(0, 0), win.x_max(), win.y_max());
	bc.add_data(5.2, "Tokyo", Color::red);
	bc.add_data(5.7, "", Color::red);
	bc.add_data(8.7, "", Color::red);
	bc.add_data(13.9, "", Color::red);
	bc.add_data(18.2, "", Color::red);
	bc.add_data(21.4, "", Color::red);
	bc.add_data(25.0, "", Color::red);
	bc.add_data(26.4, "", Color::red);
	bc.add_data(22.8, "", Color::red);
	bc.add_data(17.5, "", Color::red);
	bc.add_data(12.1, "", Color::red);
	bc.add_data(7.6, "", Color::red);

	bc.add_data(0);

	bc.add_data(6.0, "Osaka", Color::dark_green);
	bc.add_data(6.3, "", Color::dark_green);
	bc.add_data(9.4, "", Color::dark_green);
	bc.add_data(15.1, "", Color::dark_green);
	bc.add_data(19.7, "", Color::dark_green);
	bc.add_data(23.5, "", Color::dark_green);
	bc.add_data(27.4, "", Color::dark_green);
	bc.add_data(28.8, "", Color::dark_green);
	bc.add_data(25.0, "", Color::dark_green);
	bc.add_data(19.0, "", Color::dark_green);
	bc.add_data(13.6, "", Color::dark_green);
	bc.add_data(8.6, "", Color::dark_green);

	bc.add_data(0);

	bc.add_data(-0.7, "Nankyoku", Color::blue);
	bc.add_data(-2.9, "", Color::blue);
	bc.add_data(-6.5, "", Color::blue);
	bc.add_data(-10.1, "", Color::blue);
	bc.add_data(-13.5, "", Color::blue);
	bc.add_data(-15.2, "", Color::blue);
	bc.add_data(-17.3, "", Color::blue);
	bc.add_data(-19.4, "", Color::blue);
	bc.add_data(-18.1, "", Color::blue);
	bc.add_data(-13.5, "", Color::blue);
	bc.add_data(-6.8, "", Color::blue);
	bc.add_data(-1.6, "", Color::blue);

	win.attach(bc);
	win.wait_for_button();
}