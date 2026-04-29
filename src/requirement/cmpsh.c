#include"readingIns.h"
#include"executes.h"
#include <unistd.h>
#include <sys/wait.h>


int main(int argc , char **argv){
    path_list[0]="/bin";

    int status=0;
    char * line;
    char **args;
    int builtin;
    int cnt;
    int num=builtin_num(); 

    if(argc<2)
    do{
        builtin=0;
        printf("cmpsh>");
        line=readLine();
        if(line==NULL)exit(0);
        args=args_T(line);
        checkRedirect(args);
        for(int i=0;i<num;i++){
            if(strcmp(args[0],builtin_str[i])==0){
               (builtin_func[i])(args);
               builtin=1; 
               break;
            }
        }
        if(builtin==0){
            execute(args);
        }
        free(args);
      
    }
    while(status==0);
    else {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror("fopen");
            exit(1);
        }
    
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), f) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            char **args = args_T(buffer);
    
            if (args == NULL || args[0] == NULL) {
                continue;
            }
    
            builtin = 0;
            checkRedirect(args);
    
            for (int i = 0; i < num; i++) {
                if (strcmp(args[0], builtin_str[i]) == 0) {
                    status = (builtin_func[i])(args);
                    builtin = 1;
                    break;
                }
            }
    
            if (!builtin) {
                execute(args);
            }

            free(args);
        }
    
        fclose(f);
        exit(0);
    }
    

   
}