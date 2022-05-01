#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *input = malloc(sizeof(char*)), *allIn = input ;
int numStr=0;
size_t lineLen = 3;

int main() {
    printf("Enter function\n");
    /*scanf("%s", input = realloc(input, 3 * sizeof(char)));
    printf("%c", *(input+3));
    printf("%d", iscntrl(*(input+3)));
     */
    getline(&input, &lineLen, stdin);
    numStr++;
    while(strcmp( input, "$$\n") != 0) {
        printf("%s", input);
        printf("%i\n", strlen(input));
        realloc(input, lineLen);
        getline(&input, &lineLen, stdin);
        allIn = allIn + *input;
        numStr++;
        printf("%s", allIn);
    }
    return 0;
}