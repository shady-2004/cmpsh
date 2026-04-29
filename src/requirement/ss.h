
int execute(char **args) {
    char*path=getPath(args[0]);
    if(path==NULL)return 1;
    int pid=fork();
    if (pid == 0) { 
      
            int fd = open("testtesttest.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Failed to open output file");
                exit(1);  
            }

            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("Failed to redirect stdout");
                close(fd);
                exit(1); 
            }
            close(fd); 
     
        execv(path, args);  
        perror("Execv failed");
        
    } else if (pid < 0) {

        perror("Fork failed");
        return 1;
    } else {
      
        wait(NULL);

        int fd = open("testtesttest.txt", O_RDONLY);  
            if (fd == -1) {
                return 1;
            }

            char buffer[1024];
            ssize_t bytes_read;
            FILE *f=NULL;
            if(redirect==1){
               f=fopen(redirectFile,"w");
            }

            while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
                if(redirect==0)
                    write(STDOUT_FILENO, buffer, bytes_read);
                else 
                fwrite(buffer, 1, bytes_read, f);

            }
            if(f!=NULL)fclose(f);

            close(fd);
    }
    return 0;
}