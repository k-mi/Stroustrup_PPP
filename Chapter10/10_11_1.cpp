#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

const int not_a_reading = -7777;
const int not_a_month = -1;

vector<string> month_input_tb1;	// month_input_tb1[0] == "jan"

// 入力表現のvectorを初期化する
void init_input_tb1(vector<string>& tb1){
	tb1.push_back("jan");
	tb1.push_back("feb");
	tb1.push_back("mar");
	tb1.push_back("apr");
	tb1.push_back("may");
	tb1.push_back("jun");
	tb1.push_back("jul");
	tb1.push_back("aug");
	tb1.push_back("sep");
	tb1.push_back("oct");
	tb1.push_back("nov");
	tb1.push_back("dec");
}

struct Day{
	vector<double> hour;
	Day() : hour(24, not_a_reading){ }
};
	
struct Month{				// 1ヶ月分の計測値
	int month;				// [0:11] 1月は0
	vector<Day> day;		// [1:31] 1日につき計測値のvector1つ
	Month() 				// ひと月最大で31日（day[0]は使わない）
		: month(not_a_month), day(32) { }
};

struct Year{				// 1年分の計測値（月で構成される）
	int year;				// 正の数は西暦
	vector<Month> month;	// [0:11] 1月は0
	Year() : month(12) { }	// 1年につき12ヶ月
};

struct Reading{
	int day;
	int hour;
	double temperature;
};

// isから計測値rを読み取る
// フォーマット: ( 3 4 9.7 )
// フォーマットはチェックするが、データの有効性については無視する
istream& operator>>(istream& is, Reading& r){
	char ch1;
	if(is >> ch1 && ch1 != '('){
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if(!is || ch2 != ')') throw runtime_error("bad reading");	// 読み取り失敗
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}

// 簡単な評価
bool is_valid(const Reading& r){
	const int implausible_min = -200;
	const int implausible_max = 200;

	if(r.day < 1 || 31 < r.day) return false;
	if(r.hour < 0 || 23 < r.hour) return false;
	if(r.temperature < implausible_min || implausible_max < r.temperature) return false;
	return true;
}

// 終了インジゲータをチェック	
void end_of_loop(istream& ist, char term, const string& message){
	if(ist.fail()){	// termを終了インジゲータまたはセパレータとして使用する
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return;	// すべて順調
		throw runtime_error(message);
	}
}

// sは月の名前か
// その場合はそのインデックス[0:11]を返し、そうでない場合は-1を返す
int month_to_int(string s){
	for(int i = 0; i < 12; ++i)
		if(month_input_tb1[i] == s)
			return i;
	return -1;
} 

// 月の名前を返す
string int_to_month(int i){
	if(i < 0 || 12 < i) throw runtime_error("bad month index");	// 月は[0:11]
	return month_input_tb1[i];
}

// isから月をmに読み取る
// フォーマット: { month feb ... }
istream& operator>>(istream& is, Month& m){
	char ch = 0;
	if(is >> ch && ch != '{'){
		is.unget();
		is.clear(ios_base::failbit);	// Monthの読み取りに失敗した
		return is;
	}

	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if(!is || month_marker != "month") throw runtime_error("bad start of month");
	m.month = month_to_int(mm);

	Reading r;
	int duplicates = 0;
	int invailds = 0;
	while(is >> r){
		if(is_valid(r)){
			if(m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invailds;
	}
	if(invailds) throw runtime_error("invalid readings in month " + to_string(invailds));
	if(duplicates) throw runtime_error("duplicate readings in month " + to_string(duplicates));
	end_of_loop(is, '}', "bad end of month");
	return is;
}

// isから年をyに読み取る
// フォーマット: { year 1972 ... }
istream& operator>>(istream& is, Year& y){
	char ch = 0;
	if(is >> ch && ch != '{'){
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}

	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if(is.eof()) return is;		// 【追加】ファイル終了時はエラーは投げない
	if(!is || year_marker != "year") throw runtime_error("bad start of year");
	y.year = yy;

	while(true){
		Month m;	// そのつど新しいmを取得する
		if(!(is >> m)) break;
		y.month[m.month] = m;
	}

	end_of_loop(is, '}', "bad end of year");
	return is;
} 

void print_year(ostream& os, const Year& y){
	for(int i = 0; i < y.month.size(); ++i){		// Month
		const Month& m = y.month[i];
		if(m.month != not_a_month){
			os << "{ month " << int_to_month(m.month) << ' ';
			for(int j = 0; j < m.day.size(); ++j){	// Day
				const Day& d = m.day[j];
				for(int k = 0; k < d.hour.size(); ++k){
					if(d.hour[k] != not_a_reading){	// Hour
						os << "( " << j << ' ' << k << ' ' << d.hour[k] << " )";				
					}
				}
			}
			os << '}';	
		}		
	}
}

int main(){
	// 入力表現のvectorを初期化する
	init_input_tb1(month_input_tb1);

	// 入力ファイルを開く
	cout << "Plaease enter input file name\n";
	string name;
	cin >> name;
	ifstream ifs(name.c_str());
	if(!ifs) throw runtime_error("can't open input file " + name);

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// badで例外をスローする

	// 出力ファイルを開く
	cout << "Please enter output file name\n";
	cin >> name;
	ofstream ofs(name.c_str());
	if(!ofs) throw runtime_error("can't open output file " + name); 

	// 任意の数の年を読み取る
	vector<Year> ys;
	while(true){
		Year y;	// そのつど年を初期化する
		if(!(ifs >> y)) break;
		ys.push_back(y);
	}
	cout << "read " << ys.size() << " years of readings\n";

	for(int i = 0; i < ys.size(); ++i){
		ofs << "{ year " << ys[i].year << ' ';
		print_year(ofs, ys[i]);
		ofs << '}' << endl;
	}
}