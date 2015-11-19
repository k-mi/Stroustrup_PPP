#include <cmath>
#include <ctime>
#include "Graph.h"
#include "Simple_window.h"

#define M_PI (acos(-1))

int main(){
	using namespace Graph_lib;

	Simple_window win(Point(100, 100), 200, 200, "Analog clock");
	
	int center_x = win.x_max() / 2;
	int center_y = win.y_max() / 2;
	int r = min(win.x_max(), win.y_max()) / 2 - 10;

	Circle frame(Point(center_x, center_y), r);
	Circle center(Point(center_x, center_y), 10);
	center.set_fill_color(Color::black);

	win.attach(frame);
	win.attach(center);
	
	while(true){
		time_t now = time(nullptr);	// 現在時刻を取得
		tm *pnow = localtime(&now);
		
		double h_angle = M_PI / 2 - 2 * M_PI / 12 * (pnow->tm_hour % 12);
		double m_angle = M_PI / 2 - 2 * M_PI / 60 * pnow->tm_min;
		double s_angle = M_PI / 2 - 2 * M_PI / 60 * pnow->tm_sec;

		Line* h_hand = new Line(Point(center_x, center_y), Point(center_x + r / 1.2 * cos(h_angle), center_y - r / 1.2 * sin(h_angle)));
		Line* m_hand = new Line(Point(center_x, center_y), Point(center_x + r / 1.5 * cos(m_angle), center_y - r / 1.5 * sin(m_angle)));
		Line* s_hand = new Line(Point(center_x, center_y), Point(center_x + r / 1.2 * cos(s_angle), center_y - r / 1.2 * sin(s_angle)));
		h_hand->set_style(Line_style(Line_style::solid, 10));
		m_hand->set_style(Line_style(Line_style::solid, 7));
		s_hand->set_style(Line_style(Line_style::solid, 3));		
		s_hand->set_color(Color::red);

		win.attach(*h_hand);
		win.attach(*m_hand);
		win.attach(*s_hand);

		Fl::redraw();	// 描画
		Fl::wait();		
		Sleep(100);		// 100ミリ秒待機

		win.detach(*h_hand);
		win.detach(*m_hand);
		win.detach(*s_hand);

		// メモリ解放
		delete h_hand;
		delete m_hand;
		delete s_hand;
	}
}