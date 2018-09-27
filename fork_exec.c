#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include "headerfile.h"
void fork_execute(char *argv[ARG_MAX], int argc,int bgproc)
{
	int status;
    int pid = fork();
    
    if(pid == 0)
    {         
        if(bgproc == 1)
            setpgid(0,0);

        int ret = execvp(argv[0],argv);
        if(ret < 0)
            printf("Invalid Command\n");
        exit(0);
    }
    
    else if(pid != 0)
    {
        if(bgproc != 1)
        {    
            global_child = pid;
            process[pid] = malloc(sizeof(char)*(ARG_MAX+1));
            strcpy(process[pid],argv[0]);       
            waitpid(-1,&status,WUNTRACED);
            int retval = checkstatus(pid);
            if(retval==0)
            {
                process[pid]=NULL;
                free(process[pid]);
            }
        }
        
        else
        {
            process[pid] = malloc(sizeof(char)*(ARG_MAX+1));
            strcpy(process[pid],argv[0]);       
            printf("[%d]\n",pid); 
        }

    	return;
    }
}




