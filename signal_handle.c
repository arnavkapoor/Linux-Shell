#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <errno.h>
#include "headerfile.h"

void sigintHandler(int sig_num) 
{ 
	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL)
		{
			kill(i,9);
			run_or_stop[i]=0;			
			process[i]=NULL;
			free(process[i]);
		}
	}
	return;
} 

void sigstopHandler(int sig_num) 
{ 
	for (int i = 0; i < ARG_MAX*20; ++i)
	{
		if(process[i]!=NULL)
			{
				run_or_stop[i]=2;
				kill(i,20);
			}	
	}
	return;
} 