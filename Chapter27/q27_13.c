#include <stdio.h>
#include <ctype.h>	/* isspace */
#include <stdlib.h>	/* calloc */
#include <string.h> /* memcpy */

/* stdinより文字列を取得して返す。
   関数外で解放を行う必要あり */
char* cin_s(){
	int size = 0;
	int space = 8;
	char* buf = (char*)calloc(space, sizeof(char));
	char c;

	while(scanf("%1c", &c) != EOF && !isspace(c)){
		if(size + 2 >= space){
			char* tmp = (char*) calloc(space * 2, sizeof(char));
			memcpy(tmp, buf, size);
			free(buf);
			buf = tmp;
			space *= 2;
		}
		buf[size] = c;
		++size;
	}

	if(size == 0){	/* 文字が無い場合は0（ヌルポインタ）を返す */
		free(buf);
		return 0;
	}
	return buf;
}

int main(){
	while(1){
		char* string = cin_s();	/* 文字列を1つ取得 */
		if(string){
			printf("%s\n", string);
			free(string);
		}
	}
}