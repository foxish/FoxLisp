/*
 * Build with:
 * gcc -std=c11 -Wall <src> -ledit -lm
 * (ledit may be replaced by -lreadline)
 * 
 * needs libedit-dev (linux only) and mpc (https://github.com/orangeduck/mpc).
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mpc/mpc.h"

#if defined(__linux)
 
 #include <editline/readline.h>
 #include <editline/history.h>
 
#elif defined(_WIN32) || defined(_WIN64)
 static char buf[2048];
 char* readline(char* prompt){
     fputs(prompt, stdout);
     fgets(buf, 2048, stdin);
     char* line = malloc(strlen(buf)+1);
     strcpy(line, buf);
     return line;
 }
 void add_history(char* unused){};
 
#else
#error Platform not supported
#endif

mpc_parser_t* Exclamation = NULL;
mpc_parser_t* Admoniton = NULL;
mpc_parser_t* Response = NULL;

mpc_parser_t* build_parser(){
    Exclamation = mpc_new("exclamation");
    Admoniton   = mpc_new("admonition");
    Response    = mpc_new("response");

    mpca_lang(MPC_LANG_DEFAULT,
      "                                                                     \
        exclamation : /A[e]+/ | /O[i]+/;                                    \
        admonition  : /[Aa]rse/;                                            \
        response    : <exclamation> <admonition>;                           \
      ",
    Exclamation, Admoniton, Response);
    return Response;
}

int main(int argc, char** argv){
    puts("FoxList v0.0.1: Test 1 (Ctrl + C to exit)");
    while(1){
        char* buf = readline("FoxLisp> ");
        add_history(buf);
        
        //parse the input
        mpc_parser_t* parser = build_parser();
        mpc_result_t r;
    
        if (mpc_parse("<stdin>", buf, parser, &r)) {
          mpc_ast_print(r.output);
          mpc_ast_delete(r.output);
        } else {
          mpc_err_print(r.error);
          mpc_err_delete(r.error);
        }
        mpc_cleanup(3, Exclamation, Admoniton, Response);
        //end of parsing
        
        free(buf);
    }
}


