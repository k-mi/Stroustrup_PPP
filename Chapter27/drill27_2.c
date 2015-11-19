#include <stdio.h>
#include <string.h>	// strcpy, strcat, strlen
#include <stdlib.h>	// malloc

int main(){
	const char s1[] = "Hello";
	const char s2[] = "World!";
	
	char* hello = (char*)malloc(strlen(s1)+strlen(s2)+2);

	strcpy(hello, s1);
	strcat(hello, " ");
	strcat(hello, s2);

	printf("%s\n", hello);

	return 0;
}