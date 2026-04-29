#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <linux/limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define MAX_PATH 100



int redirect=0;
char*redirectFile=NULL;
 
void clear_path_list();
int checkPipes(char**args);

char *path_list[MAX_PATH];

int path_count=1;

char root='/';
int shell_exit(char**args){
    exit(0);
    return 0;
}

int shell_cd(char**args){
    if(args[1]==NULL)args[1]=&root;
    int stat=chdir(args[1]);
    if(stat==-1){
        if(redirect==1){
        FILE *f=fopen(redirectFile,"w");
        fprintf(f,"path not found");
        fclose(f);
        }else{
            printf("path not found");
        }
    }
    return 0;
}

int shell_pwd(char**args){
char path[PATH_MAX];
if(getcwd(path,sizeof(path))!=NULL){
    if(redirect==1){
        FILE *f=fopen(redirectFile,"w");
        fprintf(f,path);
        fclose(f);
    
    }else{
        printf("%s",path);
        printf("\n");
    }
}
else return 1;
return 0;
}

int shell_path(char**args){
    int i=1;
    char*arg=args[i];
    if(args[i]==NULL){
        clear_path_list();
    }
    while(arg!=NULL){
        path_list[path_count] = strdup(args[i]);
        i++;
        path_count++;
        arg=args[i];
    }
    return 0;
}

char *builtin_str[]={
    "exit",
    "cd",
    "pwd",
    "path"
};

int (*builtin_func[])(char**)={
    &shell_exit,
    &shell_cd,
    &shell_pwd,
    &shell_path
};

int builtin_num(){
    return sizeof(builtin_str)/sizeof(char*);
}

/////////////////////////////add ons

void clear_path_list(){
    for(int i=0;i<path_count;i++){
        free(path_list[i]);
        path_list[i]=NULL;
    }
    path_count=0;
}



//////////////////////////

char* getPath(char*program){
    char buffer[1024];
    for(int i=0;i<path_count;i++){
        snprintf(buffer,sizeof(buffer),"%s/%s",path_list[i],program);
        if(access(buffer,X_OK)==0){
          
            return strdup(buffer);
        
        }
    }
    return NULL;
}

int execute(char **args) {
    int num_pipes = checkPipes(args);
    int **pip = malloc(num_pipes * sizeof(int*));
    for (int i = 0; i < num_pipes; i++) {
        pip[i] = malloc(2 * sizeof(int));
        pipe(pip[i]);
    }

    int start = 0;
    for (int i = 0; i <= num_pipes; i++) {
        char *cmd[100];
        int k = 0;
        while (args[start] && strcmp(args[start], "|") != 0) {
            cmd[k++] = args[start++];
        }
        cmd[k] = NULL;  
        start++;       

        char *path = getPath(cmd[0]);
        if (!path) {
            fprintf(stderr, "Command not found: %s\n", cmd[0]);
            exit(1);
        }

        int pid = fork();
        if (pid == 0) {
            if (i != 0) {
                dup2(pip[i - 1][0], STDIN_FILENO);
            }
            if (i != num_pipes) {
                dup2(pip[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < num_pipes; j++) {
                close(pip[j][0]);
                close(pip[j][1]);
            }

            execv(path, cmd);
            perror("execv failed");
            exit(1);
        }
    }

    for (int i = 0; i < num_pipes; i++) {
        close(pip[i][0]);
        close(pip[i][1]);
    }

    for (int i = 0; i <= num_pipes; i++) {
        wait(NULL);
    }

    if (redirect == 1) {
        FILE *f = fopen(redirectFile, "w");
        if (!f) {
            perror("fopen");
            return 1;
        }

        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, bytes_read, f);
        }

        fclose(f);
    }

    for (int i = 0; i < num_pipes; i++) {
        free(pip[i]);
    }
    free(pip);

    return 0;
}



int checkRedirect(char**args){
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],">")==0){
            if(args[i+1]==NULL)return 1;
            redirect=1;
            redirectFile=strdup(args[i+1]);
            args[i]=NULL;
            args[i+1]=NULL;
            return 0;
        }
        i++;
    }
    redirect=0;
    redirectFile=NULL;
    return 0;
}

int checkPipes(char**args){
    int cnt=0;
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],"|")==0)cnt++;
        i++;
    }
    return cnt;
}
