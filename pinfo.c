#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include "headerfile.h"

void run_pinfo(char *argv[ARG_MAX] , int argc)
{

	char *my_pid = "self";

	if(argc == 2)
		my_pid = argv[1];
	
	char path1[ARG_MAX];
	sprintf(path1,"%s%s%s","/proc/",my_pid,"/status");
	
	FILE *file = fopen (path1,"r");
	if (file != NULL)
	{
		int i = 0;
		char line [128]; 
		while (fgets ( line, sizeof(line), file ) != NULL )
		{
			i++;
			if(i == 3 || i == 6 || i == 18)
				fputs (line,stdout); 
		}
		fclose ( file );
	}
	char path2[ARG_MAX];
	sprintf(path2,"%s%s%s","/proc/",my_pid,"/exe");
	
	char execpath[ARG_MAX];
	int len = readlink(path2,execpath,ARG_MAX-1);
	execpath[len] = '\0';
	printf("%s\n",execpath);
}	

