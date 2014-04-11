/*
 * Build with:
 * gcc -std=c11 -Wall <src> -ledit
 * (ledit may be replaced by -lreadline)
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char** argv){
	puts("FoxList v0.0.1: Test 1 (Ctrl + C to exit)");
	while(1){
		char* buf = readline("FoxLisp> ");
		add_history(buf);
		printf("%s\n", buf);	
		free(buf);
	}
}
