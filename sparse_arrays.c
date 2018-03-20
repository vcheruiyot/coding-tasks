#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int get_occurrence(char *delimiter, char **strings, int N){
	int count = 0;
	for(int i = 0; i < N; i++){
		if(strcmp(delimiter, strings[i]) == 0){
			count++;
		}
	}
	return count;
}
void find_occurrences(char **strings, char **queries, int string_len, int 
queries_len){
	for(int i = 0; i < queries_len; i++){
		int occurrence = get_occurrence(queries[i], strings, string_len);
		printf("%d\n", occurrence);
	}
}
int main()
{
    char* N_endptr;
    char* N_str = readline();
    int N = strtol(N_str, &N_endptr, 10);

    if (N_endptr == N_str || *N_endptr != '\0') { exit(EXIT_FAILURE); }

    char** strings_temp = split_string(readline());

    char* strings[N];

    for (int strings_itr = 0; strings_itr < N; strings_itr++) {
        char* strings_item = strings_temp[strings_itr];

        strings[strings_itr] = strings_item;
    }

    char* Q_endptr;
    char* Q_str = readline();
    int Q = strtol(Q_str, &Q_endptr, 10);

    if (Q_endptr == Q_str || *Q_endptr != '\0') { exit(EXIT_FAILURE); }

    char** queries_temp = split_string(readline());

    char* queries[Q];

    for (int queries_itr = 0; queries_itr < Q; queries_itr++) {
        char* queries_item = queries_temp[queries_itr];

        queries[queries_itr] = queries_item;
    }
	find_occurrences(strings, queries, N, Q);
    
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { 
break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
