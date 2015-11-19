#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
using namespace std;

int main(){
	srand(time(NULL));
	const int times = 10;	// 結果の取得回数（それぞれの結果の平均を結果として出力）
	clock_t t1, t2;			// 開始、終了時刻

	for(int n = 100; n <= 3000; n += 100){
		vector<int> v;
		list<int> l;

		/* vectorの計測 */
		double sum = 0;
		for(int i = 0; i < times; ++i){
			t1 = clock();
			if(t1 == clock_t(-1)) return 1;

			// ソートになる位置に乱数値を挿入
			for(int j = 0; j < n; ++j){
				vector<int>::iterator it;
				int r = rand() % n;
				for(it = v.begin(); it != v.end() && r >= *it; ++it);
				v.insert(it, r);
			}

			t2 = clock();
			if(t2 == clock_t(-1)) return 2;	

			sum += double(t2 - t1) / CLOCKS_PER_SEC;		
		}
		cout << "vector(" << n << "): " << sum / times << "[s]" << endl;

		/* listの計測 */
		sum = 0;
		for(int i = 0; i < times; ++i){
			t1 = clock();
			if(t1 == clock_t(-1)) return 1;

			// ソートになる位置に乱数値を挿入
			for(int j = 0; j < n; ++j){
				list<int>::iterator it;
				int r = rand() % n;
				for(it = l.begin(); it != l.end() && r >= *it; ++it);
				l.insert(it, r);
			}

			t2 = clock();
			if(t2 == clock_t(-1)) return 2;

			sum += double(t2 - t1) / CLOCKS_PER_SEC;		
		}
		cout << "list(" << n << "): " << sum / times << "[s]" << endl;	
	}

	return 0;
}