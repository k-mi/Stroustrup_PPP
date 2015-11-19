#include "std_lib_facilities.h"

int main(){
	int number_of_words = 0;
	string previous = " ";		// 単語としてあり得ない値
	string current;
	while(cin >> current){
		++number_of_words;		// 単語の数をインクリメントする	
		if(previous == current)
			cout << "word number " << number_of_words 
				 << " repeated: " << current << '\n';
		previous = current;
	}
}