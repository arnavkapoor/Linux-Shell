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

void run_overkill(char *argv[ARG_MAX] , int argc)
{
	if(argc != 1)
		{
			printf("wrong number of arguments\n");
			return;
		}

	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL) 
			kill(i,9);
	}
	return;		
}