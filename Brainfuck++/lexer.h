#ifndef LEXER
#define LEXER

typedef enum {
    NULLC,
    ADD,
    SUB,
    LEFT,
    RIGHT,
    LEFT_SQUARE,
    RIGHT_SQUARE,
    PRINT,
    INPUT,
    NUMBER,
    EQUALS,
    COMPARE_EQUALS,
    COMPARE_MORE,
    REGISTER_VALUE,
    REGISTER_ADRESS,
    GOTO_ADRESS,
    GOTO_VALUE,
    COMMENT,
    VAR_DECLARE,
    VAR_NAME,
    LEFT_CURLY,
    RIGHT_CURLY,
    PROC_DECLARE,
    PROC

} TOKEN;


typedef struct {
    TOKEN token;
    union {
        int numb;
        char name[64];
    } value;

} Coin;

Coin* lex(char* code, int len);
void print_lex(Coin* lex, int size);



#endif