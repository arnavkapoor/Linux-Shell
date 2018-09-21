#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include "headerfile.h"

void run_jobs(char *argv[ARG_MAX] , int argc)
{
	if(argc != 1)
		{
			printf("wrong number of arguments\n");
			return;
		}
	int priority = 1;
	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL)
			{
				if(run_or_stop[i]==1)
					printf("Running ");
					
				if(run_or_stop[i]==2)
					printf("Stopped ");
					
				printf("%d %s %d\n",priority,process[i],i);
				priority++;
			}
	}

	return;
}