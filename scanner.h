//
// Created by Seamus on 5/18/2022.
//

#ifndef PROGLANG_SCANNER_H
#define PROGLANG_SCANNER_H

typedef enum {read, write, assign, id, num, add, sub, mul, divi, lparen, rparen, eof} token;
char currToken[10];
void scan();
void error();
char commands[] = " ";//"READ A\nB = 2*A\nWRITE B+4";
int commandsInd = 0;
token tokenType;


#endif //PROGLANG_SCANNER_H
