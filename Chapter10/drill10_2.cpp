#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

struct Point{
	int x;
	int y;
};

istream& operator>>(istream& is, Point& point){
	int x = 0, y = 0;
	char ch1 = 0, ch2 = 0;
	if(is >> ch1 && ch1 != '('){
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	is >> x >> ch1 >> y >> ch2;
	if(!is) return is;
	if(ch1 != ',' || ch2 != ')') throw runtime_error("bad construction");
	point.x = x;
	point.y = y;
	return is;
}

int main(){
	vector<Point> original_points;
	Point p;

	// 入力
	for(int i = 0; i < 7; ++i){
		cout << "座標(x,y)を入力してください(" << i+1 << "回目) > ";
		do{
			cin.clear();
			cin >> p;
		} while(cin.fail());
		original_points.push_back(p);
	}
}