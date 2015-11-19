#include <stdio.h>

void C(char* p, int x){
	printf("p is \"%s\" and x is %d\n", p, x);
}

int main(){
	C("foo", 7);
	C("hoge", 1234);
	C("hogehoge", -300000);

	return 0;
}