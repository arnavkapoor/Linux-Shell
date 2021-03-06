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

void run_fg(char *argv[ARG_MAX] , int argc)
{
	int status;
	if(argc != 2)
		{
			printf("wrong number of arguments\n");
			return;
		}
	
	int priority = 1;
	int flag=0;
	
	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL)
		{
			if(priority == atoi(argv[1]))
			{
				kill(i,SIGSTOP);
				kill(i,SIGCONT);
				global_child = i;
				waitpid(i,&status,WUNTRACED);
				flag = 1;
				break;
			}
			priority++;
		}
	}
	if(flag == 0)
		printf("process doesn't exist");
	return;		

}