#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_substr(char *str, char *substr){
	if(strstr(str, substr) == NULL){
		printf("substring not in string\n");
		return;
	}
	char *copy_end;
	size_t rem_len = strlen(substr) - 1;
	char *copy_from = str + rem_len;
	
	while((copy_end = strstr(copy_from, substr))){
		size_t size = copy_end - copy_from;
		memmove(str, copy_from, size);
		str += size;
		copy_from = copy_end + rem_len;
	}
	memmove(str + rem_len, copy_from, 1 + strlen(copy_from));
	printf("%s\n", str);
	
}




int main(){
	char *str = "ab";
	char *substr = "a";
	char str_cpy[strlen(str)];
	strcpy(str_cpy, str);
	remove_substr(str_cpy, substr);
	return 0;
}