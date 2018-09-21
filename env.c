#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include "headerfile.h"

void run_setenv(char *argv[ARG_MAX] , int argc)
{
	if(argc == 1 || argc > 3)
		{
			printf("wrong number of arguments\n");
			return;
		}

	char setstring[ARG_MAX] = " ";
	if(argc == 3)
		strcpy(setstring,argv[2]);
	setenv(argv[1],setstring,1);
	return;
}

void run_unsetenv(char *argv[ARG_MAX] , int argc)
{
	if(argc != 2)
		{
			printf("wrong number of arguments\n");
			return;
		}

	unsetenv(argv[1]);
	return;
}


