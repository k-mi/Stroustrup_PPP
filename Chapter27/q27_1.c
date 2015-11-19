#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *str){
	size_t s = 0;
	while(*str++) s++; 
	return s;
}

int strcmp(const char *lhs, const char *rhs){
	while(*lhs || *rhs){
		if((!*lhs && *rhs) || *lhs < *rhs) return -1;
		else if((*lhs && !*rhs) || *lhs > *rhs) return 1;

		++lhs; ++rhs;	// 同じ文字であれば次の文字へ移動
	};

	return 0;
}	

char* strcpy(char *dest, const char *src){
	char* p = dest;
	while(*dest++ = *src++);
	return p;
}

int main(){
	const char str1[] = "Apple";
	const char str2[] = "Banana";
	char* s = (char*)malloc(strlen(str2) + 1);

	printf("%d\n", strlen(str1));
	printf("%d\n", strcmp(str1, str2));
	strcpy(s, str2);
	printf("%s\n", s);

	free(s);
}	