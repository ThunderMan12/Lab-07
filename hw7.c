#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define BUFFSIZE 4096

int main (int argc, char **argv)
{
    char buf[BUFFSIZE];
    pid_t pid;
    int status;

    if (argc != 2) {
        printf("Usage: %s <path_name>\n", argv[0]);
    }

    FILE *inputptr = fopen(argv[1], "r");
    FILE *outputptr = fopen("output.log", "w");

    while (fgets(buf, BUFFSIZE, inputptr)){
        
        pid = fork();
        if (pid == 0)
        {
            char *token;
            char *array[BUFFSIZE];
            int i = 0;
            token = strtok(buf, " ");
            do{
                array[i] = strtok(NULL, " ");
                printf("This is the element: %s\n", array[i]);
                i++;
            }
            while(array[i] != NULL);
            array[i++] =  "\0";
            printf("This is the token: %s\n", token);
            // for(int j = 0; j < BUFFSIZE; j++){
            //     if(strcmp(array[j], NULL) == 0){
            //         break;
            //     }
            //     printf("Element: %s\n", array[j]);
            // }
            execv(token, array);
            perror("execv");
            exit(-1);
        } 
        else if (pid > 0)
        {
            wait(&pid);
            if(WIFEXITED(status))
            {
                printf("Child process exited with status = %d\n", WEXITSTATUS(pid));
            } else{
                printf("Child process did not terminate normally\n");
            }
        } else{
            perror("fork");
            exit(EXIT_FAILURE);
        }

        return 0;
    }



    //use execl to replace cloned process with process at the path name

    

    




    

}