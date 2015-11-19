#include "Graph.h"

namespace Graph_lib{
	// 接続ポイントを定義するヘルパー関数
	Point n(Rectangle& r){
		return Point(r.point(0).x + r.width() / 2, r.point(0).y);
	}

	Point s(Rectangle& r){
		return Point(r.point(0).x + r.width() / 2, r.point(0).y + r.height());
	}

	Point e(Rectangle& r){
		return Point(r.point(0).x + r.width(), r.point(0).y + r.height() / 2);
	}

	Point w(Rectangle& r){
		return Point(r.point(0).x, r.point(0).y + r.height() / 2);
	}

	Point center(Rectangle& r){
		return Point(r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2);
	}

	Point ne(Rectangle& r){
		return Point(r.point(0).x + r.width(), r.point(0).y);
	}

	Point se(Rectangle& r){
		return Point(r.point(0).x + r.width(), r.point(0).y + r.height());
	}

	Point sw(Rectangle& r){
		return Point(r.point(0).x, r.point(0).y + r.height());
	}

	Point nw(Rectangle& r){
		return Point(r.point(0).x, r.point(0).y);
	}
}
