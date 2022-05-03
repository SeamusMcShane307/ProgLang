#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *input = NULL, *allIn = NULL ;
size_t lineLen = 3;

int main() {
    printf("Enter your commands\n");
    /*scanf("%s", input = realloc(input, 3 * sizeof(char)));
    printf("%c", *(input+3));
    printf("%d", iscntrl(*(input+3)));
     */
    getline(&input, &lineLen, stdin);
    printf("%i\n", sizeof(input) );
    allIn = malloc(sizeof(input));
    for( int i = 0; i < strlen(input); i++){
        printf("%i\n", i );
        *(allIn + i) = *(input + i);
    }

    while(strcmp( input, "$$\n") != 0) {
        printf("%s", input);
        printf("%i\n", strlen(input));
        printf("%s", "input memory size");
        printf("%i\n", sizeof(input) );
        printf("%s", allIn);
        printf("%i\n", strlen(allIn));

        getline(&input, &lineLen, stdin);
        if(strcmp( input, "$$\n") != 0){
            realloc(allIn, sizeof(allIn) + sizeof(input));
            strncat(allIn, input, strlen(input));
        }
    }
    free(input);
    printf("%s", allIn);
    printf("%i\n", strlen(allIn));

    /*
    char *token = NULL;
    int currToken = 0;
    while(strcmp(token, "$$") != 0){
        switch (*(all)) {

        }
    }
     */
    return 0;
}
