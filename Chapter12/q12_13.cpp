// スーパー楕円
// 参考: http://www.uja.jp/2007/09/superellipse.html

#include <cmath>
#include "Simple_window.h"
#include "Graph.h"

#define M_PI (acos(-1))

int main(){
	double a, b, m, n;	// スーパー楕円のパラメータ
	int N;				// 選択する点の数

	cin >> a >> b >> m >> n >> N;

	Simple_window win(Point(100, 100), 640, 480, "q12_13");

	const int sx = win.x_max() / 2;	// 原点
	const int sy = win.y_max() / 2;
	const int scale = 100;			// スケール
	int x, y;						// 座標
	double angle = 0;				// 角度（θ）

	Mark m0(Point(sx, sy), 'X');	// 中心点
	vector<Point> vp;

	vector<Color> vc;
	vc.push_back(Color::black);
	vc.push_back(Color::red);
	vc.push_back(Color::yellow);
	vc.push_back(Color::green);
	vc.push_back(Color::cyan);
	vc.push_back(Color::blue);
	vc.push_back(Color::magenta);
	vc.push_back(Color::white);

	Lines l[10000];					// ライン数の上限

	m = 1 / (m / 2);				// 2乗になるようにし、逆数をとる
	n = 1 / (n / 2);

	for(int i = 0; i < N; ++i){
		int rs = sin(angle) < 0 ? -1 : 1;	// sinの符号をとる
		int rc = cos(angle) < 0 ? -1 : 1;	// cosの符号をとる
		x = sx + a * scale * pow(abs(sin(angle)), m) * rs;	// 絶対値を累乗し、後で符号をかける
		y = sy - b * scale * pow(abs(cos(angle)), n) * rc;

		vp.push_back(Point(x, y));
		angle += 2 * M_PI / N;	// N角形の内角
	}

	for(int i = 0; i < vp.size(); ++i){
		for(int j = i + 1; j < vp.size(); ++j){
			l[i * j].add(vp[i], vp[j]);
			l[i * j].set_style(Line_style(Line_style::solid, 2));
			l[i * j].set_color(vc[(i * j) % 8]);
			win.attach(l[i * j]);
		}
	}

	win.attach(m0);
	win.wait_for_button();
}