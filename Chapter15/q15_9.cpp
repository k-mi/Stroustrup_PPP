#include "Graph.h"
#include <limits>

namespace Graph_lib{
	struct Collection{
		double length;	// 身長
		double data;	// 割合
	};

	// ファーマットが(length,count)であることを前提とする
	istream& operator>>(istream& is, Collection& c){
		char ch1 = 0;
		char ch2 = 0;
		char ch3 = 0;
		Collection cc;

		if(is >> ch1 >> cc.length >> ch2 >> cc.data >> ch3){
			if(ch1 != '(' || ch2 != ',' || ch3 != ')'){
				is.clear(ios_base::failbit);
				return is;
			}
		}
		else return is;

		c = cc;
		return is;
	}

	struct Data{
		Data(double d, string l, Color c) : data(d), label(l), color(c) {
			if(data <= 0) error("Bad data");
		}

		double data;	// データ
		string label;	// ラベル
		Color color;	// 色
	};

	class Line_chart : public Shape{
	public:
		Line_chart(Point xy, int w, int h);	// 棒グラフの左上の座標, 幅、高さ
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

		int m_width;			// グラフの幅
		int m_height;			// グラフの高さ
	};

	Line_chart::Line_chart(Point xy, int w, int h) : m_width(w), m_height(h), m_max(0), m_min(numeric_limits<double>::max()){
		if(m_width <= 0 || m_height <= 0) error("Bad Line_chart");
		add(xy);
	}

	void Line_chart::draw_lines() const{
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
		const int data_w = (xlength - space) / (m_data.size() * 2 - 1);	// 1つのデータの幅

		// xy軸を描画
		Axis(Axis::x, Point(point(0).x + space, point(0).y + y_orig), xlength).draw_lines();
		Axis(Axis::y, Point(point(0).x + x_orig, point(0).y + ylength + space), ylength, 10, "one notch = " + to_string(m_max / 10)).draw_lines();

		// グラフの線・ラベルを作成、描画
		Marked_polyline mp("x");
		for(int i = 0; i < m_data.size(); ++i){
			mp.add(Point(point(0).x + space + space + data_w * i * 2, point(0).y + space + ylength - m_data[i].data * yscale + 1));

			Text t(Point(mp.point(i).x, mp.point(i).y + m_data[i].data * yscale + 15), m_data[i].label);
			t.set_color(m_data[i].color);
			t.draw();
		}
		mp.draw_lines();
	}

	void Line_chart::add_data(double data, string label = "", Color color = Color::black){
		if(data > m_max) m_max = data;
		if(data < m_min) m_min = data;

		Data tmp(data, label, color);
		m_data.push_back(tmp);
	}
}

#include "Simple_window.h"

int main(){
	const string file_name = "q15_9_input.txt";
	ifstream ifs(file_name.c_str());
	if(!ifs) error("can't open ", file_name);

	Simple_window win(Point(100, 100), 1280, 720, "Height");

	Line_chart lc(Point(0, 0), win.x_max(), win.y_max());

	Collection c;
	while(ifs >> c){
		if(c.length < 0 || c.data < 0) error("out of range");

		lc.add_data(c.data, to_string(int(c.length)));

		char ch = 0;
		ifs >> ch;
		if(!ifs || ch != ',') break;	// コレクション間の区切り記号を処理
	}

	win.attach(lc);
	win.wait_for_button();
}