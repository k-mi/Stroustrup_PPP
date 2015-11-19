#include <stdio.h>
#include <string.h>	// strlen
#include <stdlib.h>	// malloc

char* cat(const char* id, const char* addr){
	int sz = strlen(id) + strlen(addr) + 2;	// 2つのCスタイルの文字、'@'、ヌル文字を合わせた長さ 
	char* res = (char*) malloc(sz);			// szバイトのメモリを割り当て
	strcpy(res, id);						// 最初にidをコピー
	res[strlen(id)] = '@';					// resのヌル文字の位置に@を配置
	strcpy(res + strlen(id) + 1, addr);		// '@'の次にaddrをコピー
	res[sz - 1] = 0;						// 最後にヌル文字
	return res;
}

char* cat2(const char* id, const char* addr){
	int id_sz = strlen(id);
	int addr_sz = strlen(addr); 
	int sz = id_sz + addr_sz + 2;	// 2つのCスタイルの文字、'@'、ヌル文字を合わせた長さ 
	char* res = (char*) malloc(sz);	// szバイトのメモリを割り当て
	strcpy(res, id);
	strcat(res, "@");	
	strcat(res, addr);
	return res;
}

int main(){
	const char id[] = "123456789";	// 文字列リテラルはC++では定数
	const char addr[] = "Tokyo";

	char* str1 = cat(id, addr);
	char* str2 = cat2(id, addr);
	printf("%s\n", str1);
	printf("%s\n", str2);

	free(str1);
	free(str2);

	return 0;
}
