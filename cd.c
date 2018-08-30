#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include "headerfile.h"


void run_cd(char *argv[ARG_MAX] , int argc)
{
	if(argc == 1)
	{
		chdir(myroot);
		return;
	}
	char path_to_go[ARG_MAX];
	if(argv[1][0] == '~')
		sprintf(path_to_go,"%s%s",myroot,&argv[1][1]);
	else
		sprintf(path_to_go,"%s",&argv[1][0]);

	DIR* dir = opendir(path_to_go);
	if (dir)
	{
	    chdir(path_to_go);
	    closedir(dir);
	}
	else if (ENOENT == errno)
	   perror("bash");
	
	return;
}