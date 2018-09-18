#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"

void run_remindme(char *argv[ARG_MAX] , int argc)
{
    int pid = fork();
    if(pid == 0)    
    {
        sleep(atoi(argv[1]));
        printf("%s\n",argv[2]);
        exit(0);
    }
    return;
}   

