#include <stdio.h>
#include <stdlib.h>

int compare_chars(const void* a, const void* b)
{
    char arg1 = *(const char*)a;
    char arg2 = *(const char*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main(){
	char key_ch[] = " 1234567890-^\\qwertyuiop@[asdfghjkl;:]zxcvbnm,./!\"#$%&'()=~|QWERTYUIOP`{ASDFGHJKL+*}ZXCVBNM<>?_";
	int size = sizeof(key_ch) / sizeof(*key_ch);
	int i = 0;

	qsort(key_ch, size, sizeof(char), compare_chars);

	for(; i < size; ++i)
		printf("%d: %c\n", key_ch[i], key_ch[i]);

	return 0;
}