#include "samples/prototypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

void initialize_matrix(int nrows, int ncols, int matrix[nrows][ncols]){
	int i, j;
	for (i = 0; i < nrows; i++){
		for(j = 0; j < ncols; j++){
			matrix[i][j] = 0;
		}
	}
}
int min(int *minimum_values){
	int min = minimum_values[0];
	for(int i = 1; i < 3; i++){
		if(minimum_values[i] < min) min = minimum_values[i];
	}
	return min;
	
}
int minimum_edit_distance(char *misspelled, char *from_dict){
	int n = strlen(misspelled);
	int m = strlen(from_dict);
	int matrix[n+1][m+1];
	initialize_matrix(n, m, matrix);
	for (int i = 1; i < n + 1; i++){
		matrix[i][0] = matrix[i-1][0] + 1;
	} 
	for(int i = 1; i < m + 1; i++){
		matrix[0][i] = matrix[0][i-1] + 1;
	}
	for(int i = 1; i < n + 1; i++){
		for(int j = 1; j < m + 1; j++){
			int minimum_values[3];
			minimum_values[0] = matrix[i - 1][j] + 1;
			minimum_values[1] = matrix[i][j-1] + 1;
			if(misspelled[i - 1] == from_dict[j - 1]){
				minimum_values[2] = matrix[i - 1][j - 1];
			}else{
				minimum_values[2] = matrix[i - 1][j - 1] + 2;
			}
			matrix[i][j] = min(minimum_values);
			int sum = m + n;
			if (matrix[i][j] > (sum - (sum >> 2))){
				return 1000;
			}
		}
	}
	return matrix[n][m];
}
void clean_up(char **dictionary, char **misspelled){
	for(int i = 0; dictionary[i]; i++){
		free(dictionary[i]);
	}
	for(int i = 0; misspelled[i]; i++){
		free(misspelled[i]);
	}
	free(misspelled);
	free(dictionary);
}
void correct_word(char **dictionary, char **misspelled){
	int score = INT_MAX;
	int name = 0;
	for(int wrong_word = 0; misspelled[wrong_word]; wrong_word++){
		for(int i = 0; dictionary[i]; i++){
			int min_score = minimum_edit_distance(misspelled[wrong_word], dictionary[i]);
			if(min_score <= score){
				score = min_score;
				name = i;
			}
		}
		score = INT_MAX;
		char *correct = dictionary[name];
		printf("wrong word = %s, correct word = %s\n", misspelled[wrong_word], correct);
		name = 0;
	}
	clean_up(dictionary, misspelled);
	
}
char **read_file(FILE *stream){
	size_t initial = 32;
	char **dictionary = malloc(sizeof(char *) * initial);
	size_t cur = 0;
	char *word;
	while((word = read_line(stream)) && strlen(word)){
		if(cur == initial){
			char **new_block = realloc(dictionary, sizeof(char *) * (initial *= 2));
			assert(new_block != NULL);
			dictionary = new_block;
		}
		dictionary[cur] = word;
		cur++;
	}
	dictionary[cur] = NULL;
	fclose(stream);
	return dictionary;
}
int main() {
	FILE *fp = fopen("samples/dictionary.txt", "r");
	FILE *stream = fopen("samples/misspelled.txt", "r");
	char **dictionary = read_file(fp);
    char **misspelled = read_file(stream);
    correct_word(dictionary, misspelled);
    return 0;
}
