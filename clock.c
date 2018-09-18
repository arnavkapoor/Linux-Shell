#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include "headerfile.h"

void print_op()
{
	char path1[ARG_MAX];
	sprintf(path1,"%s","/sys/class/rtc/rtc0/date");

	FILE *file = fopen (path1,"r");
	if (file != NULL)
	{
		char line [128]; 
		fgets ( line, sizeof(line), file );
		printf("%s  ",line);
		fclose ( file );
	}

	char path2[ARG_MAX];
	sprintf(path2,"%s","/sys/class/rtc/rtc0/time");

	FILE *file2 = fopen (path2,"r");
	if (file2 != NULL)
	{
		char line [128]; 
		fgets (line, sizeof(line), file2);
		printf("%s",line);	
		fclose (file2);
	}	
	
	return;
}


void run_clock(char *argv[ARG_MAX] , int argc)
{
    int pid = fork();
    if(pid == 0)    
    {
        int tduration = atoi(argv[4]);
        int each = atoi(argv[2]);
        int times = tduration/each;
        printf("\n");
        for (int i = 0; i < times; ++i)
        {
        	print_op();
        	sleep(each);
        	printf("\n");
        }
        exit(0);
	}
	
	return;
}   

