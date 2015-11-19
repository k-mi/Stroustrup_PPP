// 簡単なテストハーネス(26.3.2.2)の2つ目

#include <iostream>
using namespace std;

// 二分探索
template<class Iter, class T> 
bool bin_search(Iter first, Iter last, const T& value){
	Iter mid = first + (last - first) / 2;

	if(mid != last && *mid == value) return true;
	if(first == mid || mid == last) return false;
	if(*mid < value) return bin_search(mid, last, value);
	if(*mid > value) return bin_search(first, mid, value);
}

int main(){
	int a[] = { 1, 2, 3, 5, 8, 13, 21 };
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 1) == false) cout << "1 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 5) == false) cout << "2 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 8) == false) cout << "3 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 21) == false) cout << "4 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), -7) == true) cout << "5 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 4) == true) cout << "6 failed";
	if(bin_search(a, a + sizeof(a) / sizeof(*a), 22) == true) cout << "7 failed";
}