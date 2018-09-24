#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include "headerfile.h"

int checkstatus(int my_pid)
{
	char path1[ARG_MAX];
	char str[ARG_MAX];
	sprintf(str,"%d",my_pid);
	sprintf(path1,"%s%s%s","/proc/",str,"/status");
	FILE *file = fopen (path1,"r");
	if(file == NULL)
		return 0;
	
	if (file != NULL)
	{
		int i = 0;
		char line [128]; 
		while (fgets ( line, sizeof(line), file ) != NULL )
		{
			i++;
			if(i == 3)
				break;
		}
		for (int i = 0; i < 128 && line[i]!='\0'; ++i)
		{
			if(line[i] == 'T')
				return 1;		
		}
		return 2;
	}
}

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
				int retval = checkstatus(i);
				printf("%d\n",retval);
				if(retval==0)
					continue;
				if(retval==1)
					printf("Stopped ");
				if(retval==2)
					printf("Running ");
				printf("%d %s %d\n",priority,process[i],i);
				priority++;
			}
	}

	return;
}