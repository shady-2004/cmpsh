#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<string.h>
#define BUFFER 100
#define TOK_BUFF_SIZE 64
#define TOK_DELIM " \t\r\n\a"
char*readLine(){
    char * line=malloc(BUFFER*sizeof(char));
 
    if (fgets(line, BUFFER, stdin) == NULL) {
        free(line);
        return NULL;  
    }

   
    return line;
    
}
char * replace(char*tok){
    if(strcmp(tok,"''"))return strdup(" ");
    if(strcmp(tok,"'\\n'"))return strdup("\n");
    return tok;

}
char** args_T(char* line) {
    int buff = TOK_BUFF_SIZE;
    int pos = 0;
    char** tokens = malloc(buff * sizeof(char*));
    int i = 0;

    while (line[pos] != '\0') {
        while (isspace(line[pos])) pos++;  

        char* token = NULL;
        int start = pos;
        int length = 0;

        if (line[pos] == '"' || line[pos] == '\'') {
            char quote = line[pos++];
            start = pos;

            while (line[pos] != '\0' && line[pos] != quote) {
                if (line[pos] == '\\' && line[pos + 1] != '\0') pos++;  
                pos++;
            }

            length = pos - start;
            token = malloc(length + 1);
            strncpy(token, &line[start], length);
            token[length] = '\0';

            if (line[pos] == quote) pos++; 
        } else {
            start = pos;
            while (line[pos] != '\0' && !isspace(line[pos])) pos++;
            length = pos - start;
            token = malloc(length + 1);
            strncpy(token, &line[start], length);
            token[length] = '\0';
        }

        tokens[i++] = token;

        if (i >= buff) {
            buff += TOK_BUFF_SIZE;
            tokens = realloc(tokens, buff * sizeof(char*));
        }
    }

    tokens[i] = NULL;  
    return tokens;
}
