//
// Created by Seamus on 5/18/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

void error(){
    printf("%s", "syntax error\n");
    exit (1);
}

void scan(){
    int index = 0;
    for (int i = 0; i < 10; ++i) {
        currToken[i] = '\0';
    }
    while(isspace(commands[commandsInd]) > 0 ){
        commandsInd++;
    }
    if (commands[commandsInd] == EOF){
        tokenType = eof;
    }
    else if(isalpha(commands[commandsInd]) > 0) {
        while (isalnum(commands[commandsInd]) > 0){
            currToken[index] = commands[commandsInd];
            index++;
            commandsInd++;
        }
        if(strcmp(currToken, "read") > 0){
            tokenType = read;
        }
        else if(strcmp(currToken, "write") > 0){
            tokenType = write;
        }
        else tokenType = id;
    }
    else if(isdigit(commands[commandsInd]) > 0){
        while(isdigit(commands[commandsInd]) > 0){
            currToken[index] = commands[commandsInd];
            index++;
            commandsInd++;
        }
        tokenType = num;
    }
    else switch (commands[commandsInd]) {
            case '=': tokenType = assign;
            case '+': tokenType = add;
            case '-': tokenType = sub;
            case '*': tokenType = mul;
            case '/': tokenType = divi;
            case '(': tokenType = rparen;
            case ')': tokenType = lparen;
            default: error();
    }
}