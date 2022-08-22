#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

/*
program → stmt list EOF
stmt_list → stmt stmt_list | 𝝐
stmt → id = expr | read id | write expr
expr → term term_tail
term_tail → add_op term term_tail | 𝝐
term → factor factor_tail
factor_tail → mult_op factor factor_tail | 𝝐
factor → ( expr ) | id | number
add_op → + | -
mult_op → * | /
*/
struct idList
{
    char var[10];
    double value;
    struct idList *next;
};

struct idList *idListStart = NULL, *idListLast = NULL;
size_t lineLen = 3;
char tempChar[10];

void program();
void stmt_list();
void stmt();
double expr();
double term_tail();
double term();
double factor_tail();
double factor();
token add_op();
token mul_op();

void compare(token expectedToken){
    if(tokenType == expectedToken ){
        printf("%s", "The two token types are the same");
    }
    else error();
}

int inList(){
    struct idList *checker = idListStart;
    while (checker != idListLast){
        if(strcmp(checker->var, tempChar) > 0){
            return 1;
        }
        else{
            checker = checker->next;
        }
    }
    return 0;
}

void listAdd(){
    if(tokenType == id){
        char *response;
        int responseLen = getline(&response, &lineLen, stdin);
        if(idListStart == NULL){
            idListStart = malloc(sizeof(struct idList));
            strcpy(idListStart->var, currToken);

        }
        else {
            idListLast->next = malloc(sizeof(struct idList));
            idListLast = idListLast->next;
            strcpy(idListStart->var, currToken);
            idListLast->value = strtod(response, (char **) (response + responseLen));
        }
    }
    if(idListStart == NULL){
        idListStart = malloc(sizeof(struct idList));
        strcpy(idListStart->var, currToken);
    }
    else {
        idListLast->next = malloc(sizeof(struct idList));
        idListLast = idListLast->next;
        strcpy(idListStart->var, currToken);
        idListLast->value = strtod(currToken, (char **) (currToken + strlen(currToken)));
    }
}

double grabId(){
    struct idList *checker = idListStart;
    while(strcmp(currToken, idListStart->var) == 0){
        checker = checker->next;
    }
    return checker->value;
}
/*
char *input = NULL, *allIn = NULL ;
size_t lineLen = 3;
*/

int main() {
    printf("Enter your commands\n");
    program();
    /*
    scanf("%s", input = realloc(input, 3 * sizeof(char)));
    printf("%c", *(input+3));
    printf("%d", iscntrl(*(input+3)));
    */

    /*
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
    char *token = NULL;
    int currToken = 0;
    while(strcmp(token, "$$") != 0){
        switch (*(all)) {
        }
    }
     */
    return 0;
}



void program(){
    scan();
    printf("%s", "Program Started...\n");
    if (tokenType == id || tokenType == read || tokenType == write) {
        stmt_list();
        compare(eof);
        printf("%s", "EOF reached\n");
    }
    else if(tokenType == eof) {
        printf("%s", "EOF reached\n");
    }
    else error();
}

void stmt_list(){
    while(tokenType != eof){
        stmt();
    }
    printf("%s", "stmt_list complete");
}

void stmt(){
    switch (tokenType) {
        case id:
            printf("%s","Assignment Started...\n");
            if(inList() == 1){
                printf("%s", "That id has already been assigned a value");
                exit(2);
            }
            strcpy(tempChar, currToken);
            scan();
            if(commands[commandsInd+1] == '='){
                scan();
                if(tokenType == num && commands[commandsInd] != '\n') {
                    expr();
                    listAdd();
                }
                else if(tokenType == num)
                    listAdd();
                else{
                    printf("%s","Non Numeric given during assignment\n");
                    error();
                }
            }
            else error();
        case read:
            printf("%s","Read Started...\n");
            scan();
            if(inList() == 1){
                printf("%s", "Read has been called on a pre-existing variable");
                exit(2);
            }
            listAdd();
            printf("%s", "Read successfully completed");
        case write:
            printf("%s","Write Started...\n");
            scan();
            printf("%f", expr());
            printf("%s", "Write successfully completed");
        default: error();
    }
}

double expr(){
    double evalExpr = 0;
    if()
}

/*
 * term();
    scan();
    if(tokenType == eof){
        printf("%s", "stmt_list complete");
        return finalValue ;
    }
    term_tail();
    */

double term_tail(){
    double temp = 0;
    switch (tokenType) {
        case sub:
            add_op();
            temp = term();
            if(tokenType != eof ){
                temp -= term_tail();
            }
            return temp;
        case add:
            add_op();
            temp = term();
            if(tokenType != eof ){
                temp += term_tail();
            }
            return temp;
        case eof:
        default:error();
    }
}

double term(){
    double save = factor();
    factor_tail();
    if(tokenType == eof){
        printf("%s", "stmt_list complete");
        return 1;
    }
    factor_tail();
}

double factor_tail(){
    double temp;
    switch (tokenType) {
        case mul:
            mul_op();
            temp = factor();
            if( tokenType != eof){
                return temp*term_tail();
            }
            return  temp;
        case divi:
            mul_op();
            temp = factor();
            if( tokenType != eof){
                return temp/term_tail();
            }
            return temp;
        case eof:
        default:error();
    }
    if(tokenType == mul){
        scan();
        return factor();
    }
    else{

    }
}
double factor(){
    switch (tokenType) {
        case lparen:
            scan();
            return expr();
        case id:
            return grabId();
        case num:
        default: error();
    }
    scan();
}

token add_op(){
    switch (tokenType) {
        case sub:
            scan();
            return sub;
        case add:
            scan();
            return add;
        default: error();
    }
    scan();
}

token mul_op(){
    switch (tokenType) {
        case mul:
            scan();
            return mul;
        case divi:
            scan();
            return divi;
        default: error();
    }
    scan();
}
