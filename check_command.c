#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"


void select_command(char *argv[ARG_MAX], int argc,int bgproc)
{
    if (strcmp(argv[0],"pwd") == 0 || (strcmp(argv[0],"pwd&") == 0)) 
    {
        run_pwd(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"echo") == 0 || (strcmp(argv[0],"echo&") == 0)) 
    {
        run_echo(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"cd") == 0 || (strcmp(argv[0],"cd&") == 0))
    {   
        run_cd(argv, argc);
        return;
    }
    
    if (strcmp(argv[0],"ls") == 0 || (strcmp(argv[0],"ls&") == 0))
    {   
        run_ls(argv, argc); 
        return;
    }
    
    if (strcmp(argv[0],"pinfo") == 0 || (strcmp(argv[0],"pinfo&") == 0))
    {   
        run_pinfo(argv, argc); 
        return;
    }
    
    int status;
    int pid = fork();
   
    if(pid == 0)
    {    
        int ret = execvp(argv[0],argv);
        if(ret < 0)
            printf("Invalid Command\n");
    }
    
    else if(pid != 0)
    {
        if(bgproc != 1)
            waitpid(-1,&status,WUNTRACED); 
        else
            printf("%d\n",pid);
        return;
    }
}

void individual_command(char *input) // rename to find_command
{
    char* cpinput = input;
    int argc = 0;
    int maxarglength = 0;
    char* token;
    char* argv[ARG_MAX];

    token = strtok(cpinput,delimit);
    
    while (token != NULL)
    {
        argv[argc] = malloc(sizeof(char)*(strlen(token)+1));
        strcpy(argv[argc],token);
        argc++;
        token = strtok(NULL,delimit);   
    }

    int bgproc = 0;

    if(argv[argc-1][0] == '&')
        {
            bgproc = 1;
            argc--;
        }
    if(argv[argc-1][strlen(argv[argc-1])-1] == '&')
        {
            bgproc = 1;
            argv[argc-1][strlen(argv[argc-1])-1] = '\0';
        }

    argv[argc] = NULL;
    select_command(argv,argc,bgproc);

    for (int i = 0; i <= argc; ++i)
       free(argv[i]);

}
