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

void run_killjob(char *argv[ARG_MAX] , int argc)
{
	if(argc != 3)
		{
			printf("wrong number of arguments\n");
			return;
		}
	int priority = 1;
	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL)
		{
			if(priority == atoi(argv[1]))
			{
				kill(i,atoi(argv[2]));
				break;
			}
			priority++;
		}
	}
	return;		

}