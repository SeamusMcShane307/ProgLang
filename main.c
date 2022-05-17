
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
typedef enum {read, write, assign, id, num, add, sub, mul, divi, lparen, rparen, eof} token;
void error(){
    printf("%s", "syntax error\n");
    exit (1);
}

struct idList
{
    char var[10];
    double value;
    struct idList *next;
};

char commands[] = "READ A\nB:= 2*A\nWRITE B+4";
char currToken[25];
token tokenType;
struct idList *idListStart = NULL, *idListLast = NULL;
int commandsInd = 0;
size_t lineLen = 3;
double finalValue = 0;

void compare(token expectedToken){
    if(tokenType == expectedToken ){
        printf("%s", "The two token types are the same");
    }
    else error();
}


int inList(char* varName){
    struct idList *checker = idListStart;
    while (checker != idListLast){
        if(strcmp(checker->var, varName) > 0){
            return 1;
        }
        else{
            checker = checker->next;
        }
    }
    return 0;
}


token scan();
void program();
int stmt_list();
void stmt();
double expr();
double term_tail();
double term();
double factor_tail();
double factor();
token add_op();
token mul_op();

void listAdd(){
    if(tokenType == id){
        char response[10];
        int responseLen = getline(&response, &lineLen, stdin);
        if(idListStart == NULL){
            idListStart = malloc(sizeof(struct idList));
            strcpy(idListStart->var, currToken);

        }
        else {
            idListLast->next = malloc(sizeof(struct idList));
            idListLast = idListLast->next;
            strcpy(idListStart->var, currToken);
            idListLast->value = strtod(response, response + responseLen);
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
        idListLast->value = strtod(currToken, currToken + strlen(currToken));
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

token scan(){
    char currChar = ' ';
    int index = 0;
    while(isspace(currChar) > 0 ){
        currChar = commands[++commandsInd];
    }
    if (currChar == EOF){
        return  eof;
    }
    else if(isalpha(currChar) > 0) {
        while (isalnum(currChar) > 0){
            currToken[index] = currChar;
            index++;
            commandsInd++;
            currChar = commands[commandsInd];
        }
        if(strcmp(currToken, "read") > 0){
            return read;
        }
        else if(strcmp(currToken, "write") > 0){
            return write;
        }
        else return id;
    }
    else if(isdigit(currChar) > 0){
        while(isdigit(currChar) > 0){
            currToken[index] = currChar;
            index++;
            currChar = commands[++commandsInd];
        }
        return num;
    }
    else switch (currChar) {
            case '=': return assign;
            case '+': return add;
            case '-': return sub;
            case '*': return mul;
            case '/': return divi;
            case '(': return rparen;
            case ')': return lparen;
            default: error();
        }

}

void program(){
    tokenType = scan();
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

int stmt_list(){
    stmt();
    if(tokenType == eof){
        printf("%s", "stmt_list complete");
        return 1;
    }
    stmt_list();
}

void stmt(){
    switch (tokenType) {
        case id:
            if(inList(currToken) == 1){
                printf("%s", "That id has already been assigned a value");
                exit(2);
            }
            if(commands[commandsInd+1] == '='){
                printf("%s","Assignment Started...\n");
                char temp[25];
                strcpy(temp, currToken);
                scan();
                scan();
                listAdd();
            }
            else error();
        case read:
            printf("%s","Read Started...\n");
            scan();
            if(inList(currToken) == 1){
                printf("%s", "Read has been called on a pre-existing variable");
                exit(2);
            }
            listAdd();
        case write:
            printf("%s","Write Started...\n");
            scan();
            printf("%f", expr());
        default: error();
    }
}

double expr(){
    term();
    scan();
    if(tokenType == eof){
        printf("%s", "stmt_list complete");
        return finalValue ;
    }
    term_tail();
}

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
