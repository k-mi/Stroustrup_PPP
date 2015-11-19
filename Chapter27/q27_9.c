#include <stdio.h>
#include <ctype.h>	/* isspace */
#include <stdlib.h>	/* malloc, free, qsort */
#include <string.h> /* memcpy */

/* ホワイトスペース区切りでstdinから単語を読み取り、
   Cスタイルのstringへのポインタを返す */
char** getstrings(int* n){
	int words_sz = 0;		/* wordsの要素数 */
	int words_space = 4;	/* words用に確保した要素の数 */
	char** words = (char**)malloc(sizeof(char*) * words_space);

	int buf_sz = 0;		/* bufの文字数 */
	int buf_space = 8;	/* buf用に確保した要素の数 */
	char* buf = (char*)malloc(sizeof(char) * buf_space);

	char c;
	while(scanf("%1c", &c) != EOF){/* while(c = getchar() != EOF){ */
		if(isspace(c)){	/* ホワイトスペース */
			if(buf_sz <= 0) continue;

			/* wordsに追加 */
			buf[buf_sz] = '\0';		/* 最後にヌル文字を追加 */
			if(words_sz + 1 >= words_space){	/* wordsの空き要素がない */
				char** tmp = (char**)malloc(sizeof(char*) * words_space * 2);
				memcpy(tmp, words, sizeof(char*) * words_sz);
				free(words);
				words = tmp;
				words_space *= 2;
			}
			words[words_sz] = buf;
			++words_sz;

			/* bufの初期化 */
			buf_sz = 0;
			buf_space = 8;
			buf = (char*)malloc(buf_space);
		}
		else{
			if(buf_sz + 2 >= buf_space){		/* bufの空き要素がない */
				char* tmp = (char*)malloc(sizeof(char) * buf_space * 2);
				memcpy(tmp, buf, sizeof(char) * buf_sz);
				free(buf);
				buf = tmp;
				buf_space *= 2;
			}
			buf[buf_sz] = c;	/* 1文字追加 */
			++buf_sz;
		}
	}
	
	*n = words_sz;
	return words;
}

int compare_strings(const void* left, const void* right) {

    const char *left_char = *(const char **)left;
    const char *right_char = *(const char **)right;

    return strcmp(left_char, right_char);
}


int main(){
	int i, size = 0;
	char** words = getstrings(&size);

	qsort(words, size, sizeof(words), compare_strings);

	for(i = 0; i < size; ++i){
		printf("%s\n", words[i]);
		free(words[i]);
	}
	free(words);
}