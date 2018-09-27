#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "headerfile.h"


void sigHandler(int signum){
    printf("signal is %d\n",signum);
    if(global_child != -1)
        kill(global_child,signum);
    
    global_child = -1;
    return;
}


int main () {
    global_child = -1;
    main_pid = getpid();
    getcwd(myroot,ARG_MAX-1);
    strncpy(delimit," \t\r\n\v\f",6);
    
    while(1)
    {   
    	signal(SIGINT, sigHandler);     
        signal(SIGTSTP, sigHandler);     

    	prompt();
        char command[ARG_MAX];
        fgets(command,ARG_MAX,stdin);
        int status;
        
        int retval = waitpid(-1,&status,WNOHANG); 
        if(retval > 0)
           	{
           		printf("Process %s with pid %d has finished\n",process[retval],retval);
        		process[retval]=NULL;
        		free(process[retval]);
	        }

        if(strcmp(command,"\n") == 0)
           continue;
    
        if(strcmp(command,"exit\n") == 0)
            exit(0);

        char *input = strtok(command, ";");
        while(input!=NULL)
        {
            individual_command(input);
            input = strtok(NULL,";");   
        }

    }    
  
    return 0;
}
