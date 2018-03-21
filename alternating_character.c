/*
 * Solution written by Victor Cheruiyot. Feel free to use it and comment on it. 
 * It takes roughly 20 seconds for an incredibly long string... 2^500 
 * Can be optimized using look up table for the powerset.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

/*
 *In this challenge, you will be given a string. You must remove characters 
 *until the string is made up of any two alternating characters. When you 
 *choose a character to remove, all instances of that character must be removed. 
 *Your goal is to create the longest string possible that contains just two 
 *alternating letters.
 */
 

char *remove_char(char *src, char *remove){
	char *removed = malloc(sizeof(char) * strlen(src));
	int length = 0;
	for(int i = 0; i < strlen(src); i++){
		bool to_remove = false;
		for(int j = 0; j < strlen(remove); j++){
			if(src[i] == remove[j])to_remove = true;
		}
		if(!to_remove){
			removed[length] = src[i];
			length++;
		}
	}
	removed[length] = '\0';
	return removed;

}
char** find_power_set(char *elements){
	double powerset_size = pow(2, strlen(elements));
	char **powerset = malloc(sizeof(char *) * powerset_size);
	int j, count;
	int i_p = 0;
	for(count = 0; count < powerset_size; count++){
		char *subset = malloc(sizeof(char) * strlen(elements));
		int i = 0;
		for(j = 0; j < strlen(elements); j++){
			if(count & (1 << j)){
				subset[i] = elements[j];
				i++;
			}
		}
		subset[i] = '\0';
		if((strlen(elements) - 2) == strlen(subset)){
			powerset[i_p] = subset;
			i_p++;
		}
	}
	return powerset;
}
int compar(const void *p, const void *q){
	char c = *(char *)p;
	char d = *(char *)q;
	return c - d;
}
char *remove_duplicates(char *s){
	qsort(s, strlen(s), sizeof(char), compar);
	int res_ind = 1, ip_ind = 1;
	while(*(s + ip_ind)){
		if(*(s + ip_ind) != *(s + ip_ind - 1)){
			*(s + res_ind) = *(s + ip_ind);
			res_ind++;
		}
		ip_ind++;
	}
	*(s + res_ind) = '\0';
	return s;
	
}

bool validate(char *result){
	if(strlen(result) == 1 || !strlen(result)){
		return false;
	}
	char result_cpy[strlen(result)];
	strcpy(result_cpy, result);
	char *elements = remove_duplicates(result_cpy);
	if(strlen(elements) != 2){
		return false;
	}
	for(int i = 0; i < strlen(result) - 1; i++){
		if(result[i] == result[i + 1]){
			return false;
		}
	}
	return true;
}
char* get_max_string(char **powerset, char *src){
	int max = 0;
	char *final = "";
	for(int i = 0; powerset[i]; i++){
		char *to_remove = powerset[i];
		char *removed = remove_char(src, to_remove);
		bool is_valid = validate(removed);
		if(is_valid){
			if(max < strlen(removed)){
				max = strlen(removed);
				final = removed;
			}else{
				free(removed);
			}
		}else{
			free(removed);
		}
	}
	return final;
}
int main(){
	char* test = malloc(512000 * sizeof(char));
	scanf("%s", test);
	char test_cpy[strlen(test)];
	strcpy(test_cpy, test);
	char *result = remove_duplicates(test_cpy);
	char **powerset = find_power_set(result);
	char *final = get_max_string(powerset, test);
	if(!strlen(final)){
		printf("None could be formed\n");
		
	}else{
		printf("%s\n", final);
	}
}