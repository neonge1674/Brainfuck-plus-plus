#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"
#include "hash.h"

#define ARRAYSIZE 16777216
#define MAXCODESIZE 65536
#define HASHSIZE 1000

#define next_lex lex_code[codep + 1]

//For simplicity, we'll use statically allocated arrays with matching indices.
int stack[MAXCODESIZE], stackp; //to store locations of still-unmatched '['s.
int proc_stack[MAXCODESIZE], proc_stackp; 
char code[MAXCODESIZE]; int codep, codelength; //copy of the program we'll read into memory.
short int array[ARRAYSIZE]; int memp; //the memory used by the brainfuck program.
int targets[MAXCODESIZE]; //to save matching '[' for each ']' and vice versa.
int proc_targets[MAXCODESIZE];
int proc_return;

int c;
FILE *prog;

Coin* lex_code;

int cell_stack[MAXCODESIZE];
int cell_stackP = 0;

short int value_stack[MAXCODESIZE];
int value_stackP = 0;

typedef enum {
    VALUE,
    ADDRESS,
} VAR_TYPE;

typedef enum {
    NORMAL,
    VAR_NAME_READING,
    COMMENTING,
} PROGRAM_STATE;



PROGRAM_STATE prog_state = NORMAL;

short int action_sum = 0;
char* var_name;
hash_table* var_table;
hash_table* proc_table;




int charToInt(char c) 
{
    switch (c)
    {
    case '0': return 0; break;
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    case '8': return 8; break;
    case '9': return 9; break;
    default:
        return 12;
        break;
    }
}

int popValue() {
    value_stackP--;
    return value_stack[value_stackP];
}


int main(int argc, char **argv){
    if (argc > 2) fprintf(stderr, "Too many arguments.\n"), exit(1);
    if (argc < 2) fprintf(stderr, "I need a program filename.\n"), exit(1);
    if(!(prog = fopen(argv[1], "r"))) fprintf(stderr,"Can't open the file %s.\n", argv[1]),exit(1);
    codelength = fread(code, 1, MAXCODESIZE, prog);
    fclose(prog);


    var_table = new_table();
    proc_table = new_table();
    lex_code = lex(code, codelength);
    

    //print_lex(lex_code, codelength);

    



    for(codep = 0; codep < codelength; codep++){
        if (lex_code[codep].token==LEFT_SQUARE) stack[stackp++]=codep;//put each '[' on the stack
        if (lex_code[codep].token==RIGHT_SQUARE){ //If we meet a ']',
            if(stackp==0){ //and there is no '[' left on the stack, it's an error.
                fprintf(stderr,"Unmatched ']' at byte %d.", codep), exit(1);
            } else {
                --stackp; //if there is one, we take the matching '[' from the stack top,
                targets[codep]=stack[stackp]; //save it as the match for the current ']',
                targets[stack[stackp]]=codep; //and save the current ']' as the match for it.
            }
        }
    }
    if(stackp>0){ //Any unmatched '['s still left on the stack are an error too.
        fprintf(stderr,"Unmatched '[' at byte %d.", stack[--stackp]), exit(1);
    }

    for(codep = 0; codep < codelength; codep++){
        if (lex_code[codep].token == LEFT_CURLY) proc_stack[proc_stackp++]=codep;
        if (lex_code[codep].token == RIGHT_CURLY) {
            if (proc_stackp == 0) {
                fprintf(stderr,"Unmatched '}' at byte %d.", codep), exit(1);
            }
            else {
                --proc_stackp;
                proc_targets[codep] = proc_stack[proc_stackp];
                proc_targets[proc_stack[proc_stackp]] = codep;
            }
        } 
    }
    

    for (codep = 0; codep < codelength; codep++){
        if (lex_code[codep].token == PROC_DECLARE) {
            set_hash(proc_table, lex_code[codep+1].value.name, codep+2);
        }
    }



    for(codep = 0; codep < codelength; codep++){//Everything is okay; we start executing the program.
        
                
                                                                                    //Noelle's EVIL AND INTIMIDATING viewspot





         switch(lex_code[codep].token){
            //base brainfuck
            case ADD:
                switch(next_lex.token) 
                {
                case NUMBER : array[memp] += next_lex.value.numb; break;
                case GOTO_VALUE : array[memp] += popValue(); break;
                case VAR_NAME : array[memp] += array[get_hash(var_table, next_lex.value.name)]; break;

                default : array[memp]++; break;
                } break;
            case SUB: 
                switch(next_lex.token) 
                {
                case NUMBER : array[memp] -= next_lex.value.numb; break;
                case GOTO_VALUE : array[memp] -= popValue(); break;
                case VAR_NAME : array[memp] -= array[get_hash(var_table, next_lex.value.name)]; break;

                default : array[memp]--; break;
                } break;
            case LEFT: 
                switch(next_lex.token) 
                {
                case NUMBER : memp -= next_lex.value.numb; break;
                case GOTO_VALUE : memp -= popValue(); break;
                case VAR_NAME : memp -= array[get_hash(var_table, next_lex.value.name)]; break;

                default : memp--; break;
                } break;
            case RIGHT: 
                switch(next_lex.token) 
                {
                case NUMBER : memp += next_lex.value.numb; break;
                case GOTO_VALUE : memp += popValue(); break;
                case VAR_NAME : memp += array[get_hash(var_table, next_lex.value.name)]; break;

                default : memp++; break;
                } break;
            case EQUALS:
                switch(next_lex.token) 
                {
                case NUMBER : array[memp] = next_lex.value.numb; break;
                case GOTO_VALUE : array[memp] = popValue(); break;
                case VAR_NAME : array[memp] = array[get_hash(var_table, next_lex.value.name)]; break;

                default : array[memp] = 0; break;
                } break;


            case COMPARE_EQUALS:
                    switch(next_lex.token) 
                    {
                    case NUMBER : if (array[memp] == next_lex.value.numb) {array[memp] = 1;}
                                  else {array[memp] = 0;} break;
                    case GOTO_VALUE : if (array[memp] == popValue()) {array[memp] = 1;}
                                      else {array[memp] = 0;} break;
                    case VAR_NAME : if (array[memp] == array[get_hash(var_table, next_lex.value.name)]) {array[memp] = 1;}
                                    else {array[memp] = 0;} break;


                    default: if (array[memp] > 0) {array[memp] = 1;} break;
                    } break;

            case COMPARE_MORE:
                    switch(next_lex.token) 
                    {
                    case NUMBER : if (array[memp] > next_lex.value.numb) {array[memp] = 1;}
                                  else {array[memp] = 0;} break;
                    case GOTO_VALUE : if (array[memp] > popValue()) {array[memp] = 1;}
                                      else {array[memp] = 0;} break;
                    case VAR_NAME : if (array[memp] > array[get_hash(var_table, next_lex.value.name)]) {array[memp] = 1;}
                                    else {array[memp] = 0;} break;


                    default: if (array[memp] > 0) {array[memp] = 1;} break;
                    } break;
            
                        
            case REGISTER_ADRESS: cell_stack[cell_stackP++] = memp; break;
            case GOTO_ADRESS : memp = cell_stack[cell_stackP--]; break;

            case REGISTER_VALUE : value_stack[value_stackP++] = array[memp]; break;

            case VAR_DECLARE : set_hash(var_table, lex_code[codep + 1].value.name, memp); break;
                            
            case PROC : 
                    proc_return = codep;
                    codep = get_hash(proc_table, next_lex.value.name);
                    break;
                            

            case INPUT: if((c=getchar())!=EOF) array[memp]=c=='\n'?10:c; break;
            case PRINT: putchar(array[memp]==10?'\n':array[memp]); fflush(stdout); break;
            case LEFT_SQUARE: if(array[memp] == 0) codep = targets[codep]; break;
            case RIGHT_SQUARE: if(array[memp] > 0) codep = targets[codep]; break;

            case LEFT_CURLY : codep = proc_targets[codep]; break;
            case RIGHT_CURLY : codep = proc_return; proc_return = 0; break;
            

        }
    }
    exit(0);
}