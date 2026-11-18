#include "lexer.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define NUMBER_PUSH(numba) if (lexed_code[lexi - 1].token == NUMBER) \
        { \
            lexed_code[lexi - 1].value.numb *= 10; \
            lexed_code[lexi - 1].value.numb += numba; \
        } \
        else lexed_code[lexi++] = (Coin){NUMBER, numba}; \


#define PUSH_COIN(type) lexed_code[lexi++] = (Coin){type, 0};

typedef enum {
    NORMAL,
    COMMENTING,
    NAMING,
    ASCII
} LEXER_STATE;

LEXER_STATE state = NORMAL;

int nameI = 0;


Coin* lex(char* code, int len) 
{
    
    int lexi = 0;
    Coin* lexed_code = malloc(sizeof(Coin) * len);

    for (int i = 0; i < len; ++i) 
    {

    if (state == COMMENTING) 
    {
        if (code[i] == '#') {
            lexed_code[lexi++] = (Coin){COMMENT, 0};
            state = NORMAL; 
        }
        continue;
    }

    if (state == NAMING) {
        if (code[i] == '%') {
            lexed_code[lexi - 1].value.name[nameI] = '\0';
            nameI = 0;
            state = NORMAL;
        }
        else {
            lexed_code[lexi - 1].value.name[nameI] = code[i];
            nameI++;
        }
        
        continue;
    }

    if (state == ASCII) {
        NUMBER_PUSH((unsigned char)code[i])
        state = NORMAL;
    }
    
    switch (code[i]) 
    {

        case '+' : PUSH_COIN(ADD)  break;
        case '-' : PUSH_COIN(SUB)  break;
        case '<' : PUSH_COIN(LEFT)  break;
        case '>' : PUSH_COIN(RIGHT)  break;
        case '[' : PUSH_COIN(LEFT_SQUARE)  break;
        case ']' : PUSH_COIN(RIGHT_SQUARE)  break;
        case '{' : PUSH_COIN(LEFT_CURLY) break;
        case '}' : PUSH_COIN(RIGHT_CURLY) break;
        case '.' : PUSH_COIN(PRINT)  break;
        case ',' : PUSH_COIN(INPUT)  break;
        case 'e' : PUSH_COIN(EQUALS) break;
        case '=' : PUSH_COIN(COMPARE_EQUALS) break;
        case '^' : PUSH_COIN(COMPARE_MORE) break;
        case 'R' : PUSH_COIN(REGISTER_ADRESS) break;
        case 'r' : PUSH_COIN(REGISTER_VALUE) break;
        case 'G' : PUSH_COIN(GOTO_ADRESS) break;
        case 'g' : PUSH_COIN(GOTO_VALUE) break;
        case 'V' : PUSH_COIN(VAR_DECLARE) break;
        case 'P' : PUSH_COIN(PROC_DECLARE) break;
        case 'p' : PUSH_COIN(PROC) break;
        case 'A' : PUSH_COIN(ARRAY) break;
         
        case '#' : state = COMMENTING; break;
        case '%' : PUSH_COIN(VAR_NAME) state = NAMING; break;
        case '\'' : state = ASCII; break;


        case '0' : NUMBER_PUSH(0)  break;
        case '1' : NUMBER_PUSH(1)  break;
        case '2' : NUMBER_PUSH(2)  break;
        case '3' : NUMBER_PUSH(3)  break;
        case '4' : NUMBER_PUSH(4)  break;
        case '5' : NUMBER_PUSH(5)  break;
        case '6' : NUMBER_PUSH(6)  break;
        case '7' : NUMBER_PUSH(7)  break;
        case '8' : NUMBER_PUSH(8)  break;
        case '9' : NUMBER_PUSH(9)  break;
        
    }

    
    }

    return lexed_code;
}


void print_lex(Coin* lex, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        printf("{%d, %s}", lex[i].token, lex[i].value.name);
        
    }   
}
