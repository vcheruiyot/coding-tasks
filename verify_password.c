#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

/*
 * This program returns the number of characters required to make a 
 * password authentic. 
 */

int minimumNumber(int n, char* password) {
	int missing = 0;
    bool one_digit = false;
    bool english_lower = false;
    bool english_upper = false;
    bool non_alpha = false;
    for(int i = 0; i < strlen(password); i++){
        char c = password[i];
        if(isdigit(c)){
            one_digit = true;
        }
        if(isalpha(c) && islower(c)){
            english_lower = true;
        }
        if(isalpha(c) && isupper(c)){
            english_upper = true;
        }    
        if(!isalpha(c) && (c != ' ') && !isdigit(c)){
            non_alpha = true;
        }
    }
    if(!english_upper)missing++;
    if(!english_lower)missing++;
    if(!one_digit)missing++;
	if(!non_alpha)missing++;
	if(strlen(password) + missing < 6){
        missing += (6 - (strlen(password) + missing));
    }
    return missing;
}

int main() {
    int n; 
    scanf("%i", &n);
    char* password = (char *)malloc(512000 * sizeof(char));
    scanf("%s", password);
    int answer = minimumNumber(n, password);
    printf("%d\n", answer);
    return 0;
}
